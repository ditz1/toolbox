#pragma once

include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <array>
#include <cstdio>
#include <iostream>
#include <future>
#include <chrono>



std::string ExecutePythonScript(const std::string& script_path) {
  
#ifdef _WIN32
    std::string command = "py " + script_path;
#else
    std::string command = "python3 " + script_path;
#endif
    std::cout << command << script_path << std::endl;
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

int run_multi(){
  std::cout << "starting threads..." << std::endl;
    try {
      
      auto future1 = std::async(std::launch::async, ExecutePythonScript, "./test1.py");
      auto future2 = std::async(std::launch::async, ExecutePythonScript, "./test2.py");
      
      std::string result1 = future1.get();
      std::string result2 = future2.get();
      std::cout << "Result 1: " << result1;
      std::cout << "Result 2: " << result2;


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

int run() {
    std::cout << "starting main..." << std::endl;
    try {
      std::string output = ExecutePythonScript("./test1.py");
      std::cout << output;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
