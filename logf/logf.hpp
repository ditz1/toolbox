#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <iomanip>

enum LogType {
    s_,  // standard
    e_,  // error
    d_,  // debug
    i_,  // info
    w_,  // warning
    h_,  // hex
    b_,  // border
    n_,  // new line
    l_,   // no new line
};

// Function with variadic arguments
// Can also print borders
template <typename... Args>
void logf(LogType logtype, Args&&... args) {
    bool newline = true;
    switch (logtype) {
        case l_:
            newline = false;
            break;
        case s_:
            std::cout << "[LOG] ";
            break;
        case e_:
            std::cout << "[ERROR] ";
            break;
        case d_:
            std::cout << "[DEBUG] ";
            break;
        case i_:
            std::cout << "[INFO] ";
            break;
        case w_:
            std::cout << "[WARNING] ";
            break;
        case h_:
            std::cout << "0x" << std::hex;
            break;
        case n_:
            std::cout << std::endl;
            return;
        case b_:
            if constexpr (sizeof...(args) == 0) {
                for (int i = 0; i < 10; i++) {
                    std::cout << "-";
                }
                std::cout << std::endl;
                return;
            } else if constexpr (sizeof...(args) == 1) {
                const auto& border_char = std::get<0>(std::forward_as_tuple(std::forward<Args>(args)...));
                for (int i = 0; i < 10; i++) {
                    std::cout << border_char;
                }
                std::cout << std::endl;
                return;
            } else if constexpr (sizeof...(args) == 2) {
                const auto& [border_char, border_num] = std::forward_as_tuple(std::forward<Args>(args)...);
                for (int i = 0; i < static_cast<int>(border_num); i++) {
                    std::cout << border_char;
                }
                std::cout << std::endl;
                return;
            }
            break;
        default:
            break;
    }

    ((std::cout << std::forward<Args>(args)), ...);
    
    if (!newline){ return; } // else
    std::cout << std::endl;
}

// Overloaded function to handle cases where no LogType is provided
template <typename... Args>
void logf(Args&&... args) {
    ((std::cout << std::forward<Args>(args)), ...);
    std::cout << std::endl;
}
