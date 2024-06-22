import glob
import os
import shutil
import subprocess
import sys
import hashlib
import time
import argparse

### SET CONFIG HERE ###
compiler = "gcc"
compiler_flags = ["-I./include", "-std=c++17"]
linker_flags = ["-lstdc++"]
executable_name = "program"
#######################

original_executable_name = executable_name

if sys.platform == "win32":
    executable_name += ".exe"

build_dir = "build"
cache_file = os.path.join(build_dir, "makepycache.txt")
os.makedirs(build_dir, exist_ok=True)

# Support various source and header file extensions
src_extensions = ["cpp", "c", "cc"]
header_extensions = ["h", "hpp", "hh"]

src_files = []
for ext in src_extensions:
    src_files.extend(glob.glob(f"src/**/*.{ext}", recursive=True))
header_files = []
for ext in header_extensions:
    header_files.extend(glob.glob(f"include/**/*.{ext}", recursive=True))

def check_compiler():
    global compiler
    if not compiler:
        compilers = ["gcc", "clang", "cl.exe"]
        for c in compilers:
            try:
                subprocess.run([c, "--version"], check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
                compiler = c
                break
            except FileNotFoundError:
                pass
        if not compiler:
            print("no suitable compiler found. Please make sure gcc, clang, or cl.exe is installed and available in the system PATH.")
            sys.exit(1)

def load_cache():
    cache = {}
    if os.path.exists(cache_file):
        with open(cache_file, "r") as f:
            for line in f:
                file, hash_value = line.strip().split(":")
                cache[file] = hash_value
    return cache

def save_cache(cache):
    with open(cache_file, "w") as f:
        for file, hash_value in cache.items():
            f.write(f"{file}:{hash_value}\n")

def get_file_hash(file):
    with open(file, "rb") as f:
        return hashlib.md5(f.read()).hexdigest()

def compile_file(file, cache, progress):
    ext = os.path.splitext(file)[1]
    obj_file = os.path.join(build_dir, file.replace(ext, ".o"))
    os.makedirs(os.path.dirname(obj_file), exist_ok=True)
    
    file_hash = get_file_hash(file)
    dependencies_changed = any(get_file_hash(header) != cache.get(header, "") for header in header_files)
    
    if file in cache and cache[file] == file_hash and not dependencies_changed and os.path.exists(obj_file):
        print(f"skipping {file} [{progress:.2f}%]")
    else:
        print(f"compiling {file} [{progress:.2f}%]")
        subprocess.run([compiler, "-c", file, "-o", obj_file] + compiler_flags, check=True)
        cache[file] = file_hash

def compile_files(src_files, header_files, cache):
    total_files = len(src_files)
    for index, file in enumerate(src_files, start=1):
        progress = (index / total_files) * 100
        compile_file(file, cache, progress)

    for header in header_files:
        cache[header] = get_file_hash(header)

def link_files(obj_files):
    print(f"--- linking {executable_name} ---")
    subprocess.run([compiler, "-o", os.path.join(build_dir, executable_name)] + obj_files + linker_flags, check=True)

def clean_build():
    shutil.rmtree(build_dir, ignore_errors=True)
    if os.path.exists(executable_name):
        os.remove(executable_name)
    if os.path.exists("Makefile"):
        os.remove("Makefile")
    print("build directory and executable cleaned.")

def run_executable():
    executable_path = os.path.abspath(executable_name)
    print(f"--- running {original_executable_name} ---")
    subprocess.run(executable_path)

def generate_makefile():
    with open("Makefile", "w") as f:
        f.write(f"CC = {compiler}\n")
        f.write(f"CFLAGS = {' '.join(compiler_flags)}\n")
        f.write(f"LDFLAGS = {' '.join(linker_flags)}\n")
        f.write(f"TARGET = {executable_name}\n")
        f.write("BUILD_DIR = build\n\n")

        obj_files = [os.path.join("$(BUILD_DIR)", os.path.relpath(file, "src").replace(os.path.splitext(file)[1], ".o")) for file in src_files]
        f.write(f"OBJS = {' '.join(obj_files)}\n\n")

        f.write("all: $(TARGET)\n\n")
        f.write("$(TARGET): $(OBJS)\n")
        f.write("\t$(CC) $(OBJS) -o $@ $(LDFLAGS)\n\n")

        for ext in src_extensions:
            f.write(f"$(BUILD_DIR)/%.o: src/%.{ext}\n")
            f.write("\t@mkdir -p $(@D)\n")
            f.write("\t$(CC) $(CFLAGS) -c $< -o $@\n\n")

        f.write(".PHONY: clean\n\n")

        f.write("clean:\n")
        if sys.platform == "win32":
            f.write("\tif exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)\n")
            f.write("\tif exist $(TARGET) del $(TARGET)\n")
        else:
            f.write("\trm -rf $(BUILD_DIR) $(TARGET)\n")

    print("--- makefile generated ---")
    
def main():
    print("\n ### make.py ### \n")
    parser = argparse.ArgumentParser(description="build script")
    parser.add_argument("action", nargs="?", default="build", 
                        choices=["build", "b", "run", "r", "clean", "c", "rebuild", "rb", "makefile", "m"],
                        help="action to perform (default: build)")
    args = parser.parse_args()

    if args.action in ["clean", "c"]:
        clean_build()
        return

    if args.action in ["makefile", "m"]:
        generate_makefile()
        return

    check_compiler()
    cache = load_cache()

    if args.action in ["build", "b", "run", "r", "rebuild", "rb"]:
        if args.action in ["rebuild", "rb"]:
            clean_build()

        print("--- compiling ---")
        start_time = time.time()
        compile_files(src_files, header_files, cache)
        obj_files = [os.path.join(build_dir, file.replace(os.path.splitext(file)[1], ".o")) for file in src_files]
        print("\n")
        compile_time = time.time() - start_time
        print(f"compilation time: {compile_time:.2f} seconds \n")

        start_time = time.time()
        link_files(obj_files)
        shutil.move(os.path.join(build_dir, executable_name), executable_name)
        link_time = time.time() - start_time
        print(f"linking time: {link_time:.2f} seconds")

        print("\n")
        print(f'--- "{original_executable_name}" was created ---')

        save_cache(cache)

        if args.action in ["run", "r"]:
            run_executable()

if __name__ == "__main__":
    main()