#include "../include/bitsplitter.hpp"

// generic function to split float into 4 bytes
std::vector<int8_t> ToInt8s(float f){
    std::vector<int8_t> asbits;
    FloatAndBits fb;
    fb.f = f;
    asbits.push_back(fb.bits.b0);
    asbits.push_back(fb.bits.b1);
    asbits.push_back(fb.bits.b2);
    asbits.push_back(fb.bits.b3);
    
    return {asbits};
}

void PrintBits(std::vector<int8_t> bits){
    for (auto b : bits){
        std::cout << std::bitset<8>(b) << " ";
    }
    std::cout << std::endl;
}

void hexPrintBits(std::vector<int8_t> bits){
    for (auto b : bits){
        printf("0x%x ", b); // for some reason std::hex breaks with this
    }
    std::cout << std::endl;
}
