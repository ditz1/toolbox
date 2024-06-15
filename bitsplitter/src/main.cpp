#include "../include/bitsplitter.hpp"

void printbits(float f, std::vector<int8_t> bits){
    std::cout << std::endl;
    std::cout << "Float: " << f << std::endl;
    hexPrintBits(bits);
    PrintBits(bits);
}


int main (int argc, char** argv) {
    std::cout << "Split These Bits" << std::endl;
    
    float f = 123.456;
    float a = 0.0;
    float b = 1.0;
    float c = 2.0;
    float d = 10.0;
    float e = 10;
    float g = 100;
    float h = 1000;

    std::vector<int8_t> bits = ToInt8s(f);

    printbits(f, bits);
    printbits(a, ToInt8s(a));
    printbits(b, ToInt8s(b));
    printbits(c, ToInt8s(c));
    printbits(d, ToInt8s(d));
    printbits(e, ToInt8s(e));
    printbits(g, ToInt8s(g));
    printbits(h, ToInt8s(h));

    
    return 0;
}




