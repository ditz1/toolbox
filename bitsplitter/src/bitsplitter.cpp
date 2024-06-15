#include "bitsplitter.hpp"
#include <iostream>
#include <bitset>

// Function to print bits
void PrintBits(const std::vector<int8_t>& bits) {
    for (size_t i = 0; i < bits.size(); ++i) {  // Iterate over each bit
        std::cout << std::bitset<8>(bits[i]) << " ";  // Print the bit as a bitset
    }
    std::cout << std::endl;  // Print a newline character
}

// Function to print bits in hexadecimal format
void HexPrintBits(const std::vector<int8_t>& bits) {
    for (auto b : bits) {  // Iterate over each bit
        printf("0x%02x ", static_cast<unsigned int>(b));  // Print the bit in hexadecimal format
    }
    std::cout << std::endl;  // Print a newline character
}