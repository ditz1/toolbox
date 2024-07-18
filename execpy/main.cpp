#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <array>
#include <cstdio>

std::string ExecutePythonScript(const std::string& script_path) {

#ifdef _WIN32
    std::string command = "py " + script_path;
#else
    std::string command = "python3 " + script_path;
#endif
    std::array<char, 128> buffer;
    std::string result;


#ifdef _WIN32
    FILE* pipe = _popen(command.c_str(), "r");
#else
    FILE* pipe = popen(command.c_str(), "r");
#endif

    if (!pipe) {
        throw std::runtime_error("Failed to open pipe");
    }

    try {
        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            result += buffer.data();
        }
    } catch (...) {
        #ifdef _WIN32
            _pclose(pipe);
        #else
            pclose(pipe);
        #endif
        throw;
    }

    #ifdef _WIN32
    _pclose(pipe);
    #else
    pclose(pipe);
    #endif

    return result;
}

int main() {
    try {
        std::string output = ExecutePythonScript("./test.py");
        std::cout << "output: " << output;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}