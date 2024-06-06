#include "logf.hpp"
#include <stdint.h>

uint8_t a = 255;
uint16_t b = 65535;
uint32_t c = 4294967295;
uint64_t d = 18446744073709551615;
int e = static_cast<int>(sizeof(int));
float f = static_cast<float>(sizeof(float));
double g = static_cast<double>(sizeof(double));
long h = static_cast<long>(sizeof(long));
long long i = static_cast<long long>(sizeof(long long));
unsigned int j = static_cast<unsigned int>(sizeof(unsigned int));
char k = 'A';
unsigned char l = static_cast<unsigned char>(sizeof(unsigned char));
size_t s = 100;
std::string str = "string";

int main() {
    logf(b_);
    logf(b_, "@");
    logf(b_, "#", 10);
    logf("This is a test of logf!");
    logf(s_, "Standard message");
    logf(e_, "Error message");
    logf(d_, "Debug message");
    logf(i_, "Info message");
    logf(w_, "Warning message");
    logf(n_, "New Line (and another after this)");
    logf(n_);
    logf(b_, "@", 2);
    logf(b_, "#", 4);
    logf(b_, "$", 6);
    logf(b_, "%", 8);
    logf(b_, "^", 6);
    logf(b_, "&", 4);
    logf(b_, "*", 2);
    logf(n_);
    logf("_l_", "o_", "g_", "f_");
    
    logf(i_, "uint8's must be prefixed with '+'");
    logf("uint8: ", +a);
    
    logf(i_, "you can also use the h_ prefix for hex");
    logf(l_, "uint8 (hex): ");
    logf(h_, a);
    
    logf("uint16: ", b);
    logf(l_, "uint16 (hex): ");
    logf(h_, b);
    
    logf("uint32: ", c);
    logf(l_, "uint32 (hex): ");
    logf(h_, c);

    logf("uint64: ", d);
    logf(l_, "uint64 (hex): ");
    logf(h_, d);
    
    logf("int: ", e);
    logf("float: ", f);
    logf("double: ", g);
    logf("long: ", h);
    logf("long long: ", i);
    logf("unsigned int: ", j);
    logf("char: ", k);
    logf("unsigned char: ", l);
    logf("size_t: ", s);
    logf("string: ", str);
    logf("a: ", +a, " b: ", b, " c: ", c, " d: ", d);
    return 0;
}
