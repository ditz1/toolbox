#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <bitset>
#include <cstdint>
#include <stdio.h>

// technically, its not splitting bits. its splitting bytes. but this sounds much better

// union to split float into 4 bytes
typedef union FloatAndBits{
    float f;
    struct {
        int32_t b0 : 8;
        int32_t b1 : 8;
        int32_t b2 : 8;
        int32_t b3 : 8;
    } bits;
} FloatAndBits;

std::vector<int8_t> ToInt8s(float f);
void PrintBits(std::vector<int8_t> bits);
void hexPrintBits(std::vector<int8_t> bits);