#include "bitsplitter.hpp"
#include <iostream>
#include <vector>

int main() {

    // Test splitting bits using the SplitBits macro
    uint8_t byte = 0xAB;
    auto splitBits8 = SplitBits(uint8_t, byte, 4, 4);
    std::cout << "Byte: 0x" << std::hex << static_cast<int>(byte) << std::dec << std::endl;
    std::cout << "Split Bits (8-bit): ";
    PrintBits(splitBits8);
    std::cout << "Hex: ";
    HexPrintBits(splitBits8);
    std::cout << std::endl;

    uint16_t word = 0xABCD;
    auto splitBits16 = SplitBits(uint16_t, word, 4, 4, 8);
    std::cout << "Word: 0x" << std::hex << word << std::dec << std::endl;
    std::cout << "Split Bits (16-bit): ";
    PrintBits(splitBits16);
    std::cout << "Hex: ";
    HexPrintBits(splitBits16);
    std::cout << std::endl;

    uint32_t dword = 0xABCDEF01;
    auto splitBits32 = SplitBits(uint32_t, dword, 8, 8, 8, 8);
    std::cout << "Double Word: 0x" << std::hex << dword << std::dec << std::endl;
    std::cout << "Split Bits (32-bit): ";
    PrintBits(splitBits32);
    std::cout << "Hex: ";
    HexPrintBits(splitBits32);
    std::cout << std::endl;

    uint64_t qword = 0xABCDEF0123456789;
    auto splitBits64 = SPLIT_BITS(uint64_t, qword, 16, 16, 16, 16);
    std::cout << "Quad Word: 0x" << std::hex << qword << std::dec << std::endl;
    std::cout << "Split Bits (64-bit): ";
    PrintBits(splitBits64);
    std::cout << "Hex: ";
    HexPrintBits(splitBits64);
    std::cout << std::endl;

    return 0;  // Return 0 to indicate successful execution
}