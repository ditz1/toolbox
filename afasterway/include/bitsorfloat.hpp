#pragma once
#include <vector>
#include <bitset>
#include <string>
#include <stdio.h>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <memory>
#include <chrono>
#include <random>

enum class Group {
    A, B, C, D, E, F
};

enum class AnotherGroup {
    U, W, X, Y, Z
};

union BitsOrFloat {
    float f;
    struct {
        uint8_t b0, b1, b2, b3;
    } bytes;
};

struct Entry {
    Group group;
    AnotherGroup another_group;
    BitsOrFloat data;
    
    Entry(Group g, AnotherGroup ag, BitsOrFloat d)
        : group(g), another_group(ag), data(d) {}
    
    int32_t as_int32_cpp() {
        return *reinterpret_cast<int32_t*>(&data);
    }
    int32_t as_int32() const {
        int32_t x;
        memcpy(&x, &data, sizeof(int32_t));
        return x;
    }
    std::unique_ptr<uint8_t[]> reverse_order() {
        auto reversed = std::make_unique<uint8_t[]>(4);
        reversed[0] = data.bytes.b3;
        reversed[1] = data.bytes.b2;
        reversed[2] = data.bytes.b1;
        reversed[3] = data.bytes.b0;
        return reversed;
    }
    void printbytes() const {
        printf("float: %f\n", data.f);
        printf("hex: | %x | %x | %x | %x |\n", data.bytes.b3, data.bytes.b2, data.bytes.b1, data.bytes.b0);
        printf("int32_t: 0x%x\n", as_int32());
    }
};

class Record {
public:    
    Record(std::vector<Entry> data) : _data(data) {}
    inline std::vector<Entry>& datar() { return _data; }
    inline const std::vector<Entry>& datar() const { return _data; }
    inline std::vector<Entry>* datap() { return &_data; }
    inline Entry& data() { return _data.front(); }
    void AddEntry(Entry e);
    void AddEntries(std::vector<Entry> entries);
    void PrintAllEntries();
    void PrintGroupEntries(Group g);
    void PrintAnotherGroupEntries(AnotherGroup ag);
private:
    std::vector<Entry> _data;
    int k;
};

Group GroupFromString(const char* s);
AnotherGroup AnotherGroupFromString(const char* s);