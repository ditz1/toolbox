#pragma once
#include <vector>
#include <cstdint>
#include <type_traits>
#include <stdexcept>

// Helper function to calculate the sum of bit sizes
template <int... Bits>
constexpr int SumBits() {
    return (... + Bits);
}

// BitSplitter union template for 8-bit primitives
template <typename T, int... Bits>
union BitSplitter8 {
    static_assert(std::is_integral_v<T> && sizeof(T) == 1, "T must be an 8-bit integral type");
    static_assert(sizeof...(Bits) > 0, "At least one bit size must be specified");
    static_assert(SumBits<Bits...>() <= 8, "Total bit sizes exceed the size of T");

    T value;

    struct {
        T b0 : Bits;
        T b1 : (sizeof...(Bits) >= 2 ? Bits : 0);
        T b2 : (sizeof...(Bits) >= 3 ? Bits : 0);
        T b3 : (sizeof...(Bits) >= 4 ? Bits : 0);
        T b4 : (sizeof...(Bits) >= 5 ? Bits : 0);
        T b5 : (sizeof...(Bits) >= 6 ? Bits : 0);
        T b6 : (sizeof...(Bits) >= 7 ? Bits : 0);
        T b7 : (sizeof...(Bits) == 8 ? Bits : 0);
    } bits;

    BitSplitter8(T val) : value(val) {}
};

// BitSplitter union template for 16-bit primitives
template <typename T, int... Bits>
union BitSplitter16 {
    static_assert(std::is_integral_v<T> && sizeof(T) == 2, "T must be a 16-bit integral type");
    static_assert(sizeof...(Bits) > 0, "At least one bit size must be specified");
    static_assert(SumBits<Bits...>() <= 16, "Total bit sizes exceed the size of T");

    T value;

    struct {
        T b0 : Bits;
        T b1 : (sizeof...(Bits) >= 2 ? Bits : 0);
        T b2 : (sizeof...(Bits) >= 3 ? Bits : 0);
        T b3 : (sizeof...(Bits) >= 4 ? Bits : 0);
        T b4 : (sizeof...(Bits) >= 5 ? Bits : 0);
        T b5 : (sizeof...(Bits) >= 6 ? Bits : 0);
        T b6 : (sizeof...(Bits) >= 7 ? Bits : 0);
        T b7 : (sizeof...(Bits) == 8 ? Bits : 0);
        T b8 : (sizeof...(Bits) >= 9 ? Bits : 0);
        T b9 : (sizeof...(Bits) >= 10 ? Bits : 0);
        T b10 : (sizeof...(Bits) >= 11 ? Bits : 0);
        T b11 : (sizeof...(Bits) >= 12 ? Bits : 0);
        T b12 : (sizeof...(Bits) >= 13 ? Bits : 0);
        T b13 : (sizeof...(Bits) >= 14 ? Bits : 0);
        T b14 : (sizeof...(Bits) >= 15 ? Bits : 0);
        T b15 : (sizeof...(Bits) == 16 ? Bits : 0);
    } bits;

    BitSplitter16(T val) : value(val) {}
};

// BitSplitter union template for 32-bit primitives
template <typename T, int... Bits>
union BitSplitter32 {
    static_assert(std::is_integral_v<T> && sizeof(T) == 4, "T must be a 32-bit integral type");
    static_assert(sizeof...(Bits) > 0, "At least one bit size must be specified");
    static_assert(SumBits<Bits...>() <= 32, "Total bit sizes exceed the size of T");

    T value;

    struct {
        T b0 : Bits;
        T b1 : (sizeof...(Bits) >= 2 ? Bits : 0);
        T b2 : (sizeof...(Bits) >= 3 ? Bits : 0);
        T b3 : (sizeof...(Bits) >= 4 ? Bits : 0);
        T b4 : (sizeof...(Bits) >= 5 ? Bits : 0);
        T b5 : (sizeof...(Bits) >= 6 ? Bits : 0);
        T b6 : (sizeof...(Bits) >= 7 ? Bits : 0);
        T b7 : (sizeof...(Bits) == 8 ? Bits : 0);
        T b8 : (sizeof...(Bits) >= 9 ? Bits : 0);
        T b9 : (sizeof...(Bits) >= 10 ? Bits : 0);
        T b10 : (sizeof...(Bits) >= 11 ? Bits : 0);
        T b11 : (sizeof...(Bits) >= 12 ? Bits : 0);
        T b12 : (sizeof...(Bits) >= 13 ? Bits : 0);
        T b13 : (sizeof...(Bits) >= 14 ? Bits : 0);
        T b14 : (sizeof...(Bits) >= 15 ? Bits : 0);
        T b15 : (sizeof...(Bits) == 16 ? Bits : 0);
        T b16 : (sizeof...(Bits) >= 17 ? Bits : 0);
        T b17 : (sizeof...(Bits) >= 18 ? Bits : 0);
        T b18 : (sizeof...(Bits) >= 19 ? Bits : 0);
        T b19 : (sizeof...(Bits) >= 20 ? Bits : 0);
        T b20 : (sizeof...(Bits) >= 21 ? Bits : 0);
        T b21 : (sizeof...(Bits) >= 22 ? Bits : 0);
        T b22 : (sizeof...(Bits) >= 23 ? Bits : 0);
        T b23 : (sizeof...(Bits) == 24 ? Bits : 0);
        T b24 : (sizeof...(Bits) >= 25 ? Bits : 0);
        T b25 : (sizeof...(Bits) >= 26 ? Bits : 0);
        T b26 : (sizeof...(Bits) >= 27 ? Bits : 0);
        T b27 : (sizeof...(Bits) >= 28 ? Bits : 0);
        T b28 : (sizeof...(Bits) >= 29 ? Bits : 0);
        T b29 : (sizeof...(Bits) >= 30 ? Bits : 0);
        T b30 : (sizeof...(Bits) >= 31 ? Bits : 0);
        T b31 : (sizeof...(Bits) == 32 ? Bits : 0);
    } bits;

    BitSplitter32(T val) : value(val) {}
};

// BitSplitter union template for 64-bit primitives
template <typename T, int... Bits>
union BitSplitter64 {
    static_assert(std::is_integral_v<T> && sizeof(T) == 8, "T must be a 64-bit integral type");
    static_assert(sizeof...(Bits) > 0, "At least one bit size must be specified");
    static_assert(SumBits<Bits...>() <= 64, "Total bit sizes exceed the size of T");

    T value;

    struct {
        T b0 : Bits;
        T b1 : (sizeof...(Bits) >= 2 ? Bits : 0);
        T b2 : (sizeof...(Bits) >= 3 ? Bits : 0);
        T b3 : (sizeof...(Bits) >= 4 ? Bits : 0);
        T b4 : (sizeof...(Bits) >= 5 ? Bits : 0);
        T b5 : (sizeof...(Bits) >= 6 ? Bits : 0);
        T b6 : (sizeof...(Bits) >= 7 ? Bits : 0);
        T b7 : (sizeof...(Bits) == 8 ? Bits : 0);
        T b8 : (sizeof...(Bits) >= 9 ? Bits : 0);
        T b9 : (sizeof...(Bits) >= 10 ? Bits : 0);
        T b10 : (sizeof...(Bits) >= 11 ? Bits : 0);
        T b11 : (sizeof...(Bits) >= 12 ? Bits : 0);
        T b12 : (sizeof...(Bits) >= 13 ? Bits : 0);
        T b13 : (sizeof...(Bits) >= 14 ? Bits : 0);
        T b14 : (sizeof...(Bits) >= 15 ? Bits : 0);
        T b15 : (sizeof...(Bits) == 16 ? Bits : 0);
        T b16 : (sizeof...(Bits) >= 17 ? Bits : 0);
        T b17 : (sizeof...(Bits) >= 18 ? Bits : 0);
        T b18 : (sizeof...(Bits) >= 19 ? Bits : 0);
        T b19 : (sizeof...(Bits) >= 20 ? Bits : 0);
        T b20 : (sizeof...(Bits) >= 21 ? Bits : 0);
        T b21 : (sizeof...(Bits) >= 22 ? Bits : 0);
        T b22 : (sizeof...(Bits) >= 23 ? Bits : 0);
        T b23 : (sizeof...(Bits) == 24 ? Bits : 0);
        T b24 : (sizeof...(Bits) >= 25 ? Bits : 0);
        T b25 : (sizeof...(Bits) >= 26 ? Bits : 0);
        T b26 : (sizeof...(Bits) >= 27 ? Bits : 0);
        T b27 : (sizeof...(Bits) >= 28 ? Bits : 0);
        T b28 : (sizeof...(Bits) >= 29 ? Bits : 0);
        T b29 : (sizeof...(Bits) >= 30 ? Bits : 0);
        T b30 : (sizeof...(Bits) >= 31 ? Bits : 0);
        T b31 : (sizeof...(Bits) == 32 ? Bits : 0);
        T b32 : (sizeof...(Bits) >= 33 ? Bits : 0);
        T b33 : (sizeof...(Bits) >= 34 ? Bits : 0);
        T b34 : (sizeof...(Bits) >= 35 ? Bits : 0);
        T b35 : (sizeof...(Bits) >= 36 ? Bits : 0);
        T b36 : (sizeof...(Bits) >= 37 ? Bits : 0);
        T b37 : (sizeof...(Bits) >= 38 ? Bits : 0);
        T b38 : (sizeof...(Bits) >= 39 ? Bits : 0);
        T b39 : (sizeof...(Bits) == 40 ? Bits : 0);
        T b40 : (sizeof...(Bits) >= 41 ? Bits : 0);
        T b41 : (sizeof...(Bits) >= 42 ? Bits : 0);
        T b42 : (sizeof...(Bits) >= 43 ? Bits : 0);
        T b43 : (sizeof...(Bits) >= 44 ? Bits : 0);
        T b44 : (sizeof...(Bits) >= 45 ? Bits : 0);
        T b45 : (sizeof...(Bits) >= 46 ? Bits : 0);
        T b46 : (sizeof...(Bits) >= 47 ? Bits : 0);
        T b47 : (sizeof...(Bits) == 48 ? Bits : 0);
        T b48 : (sizeof...(Bits) >= 49 ? Bits : 0);
        T b49 : (sizeof...(Bits) >= 50 ? Bits : 0);
        T b50 : (sizeof...(Bits) >= 51 ? Bits : 0);
        T b51 : (sizeof...(Bits) >= 52 ? Bits : 0);
        T b52 : (sizeof...(Bits) >= 53 ? Bits : 0);
        T b53 : (sizeof...(Bits) >= 54 ? Bits : 0);
        T b54 : (sizeof...(Bits) >= 55 ? Bits : 0);
        T b55 : (sizeof...(Bits) == 56 ? Bits : 0);
        T b56 : (sizeof...(Bits) >= 57 ? Bits : 0);
        T b57 : (sizeof...(Bits) >= 58 ? Bits : 0);
        T b58 : (sizeof...(Bits) >= 59 ? Bits : 0);
        T b59 : (sizeof...(Bits) >= 60 ? Bits : 0);
        T b60 : (sizeof...(Bits) >= 61 ? Bits : 0);
        T b61 : (sizeof...(Bits) >= 62 ? Bits : 0);
        T b62 : (sizeof...(Bits) >= 63 ? Bits : 0);
        T b63 : (sizeof...(Bits) == 64 ? Bits : 0);
    } bits;

    BitSplitter64(T val) : value(val) {}
};

// Function to split bits using variadic template parameters
template <typename T, int... Bits>
std::vector<int8_t> SplitBits(T value) {
    if constexpr (sizeof(T) == 1) {
        BitSplitter8<T, Bits...> splitter(value);
        std::vector<int8_t> result;
        result.push_back(static_cast<int8_t>(splitter.bits.b0));
        for (int i = 1; i < 8; ++i) {
            if constexpr (i < sizeof...(Bits)) {
                result.push_back(static_cast<int8_t>(splitter.bits.b[i]));
            }
        }
        return result;
    } else if constexpr (sizeof(T) == 2) {
        BitSplitter16<T, Bits...> splitter(value);
        std::vector<int8_t> result;
        result.push_back(static_cast<int8_t>(splitter.bits.b0));
        for (int i = 1; i < 16; ++i) {
            if constexpr (i < sizeof...(Bits)) {
                result.push_back(static_cast<int8_t>(splitter.bits.b[i]));
            }
        }
        return result;
    } else if constexpr (sizeof(T) == 4) {
        BitSplitter32<T, Bits...> splitter(value);
        std::vector<int8_t> result;
        result.push_back(static_cast<int8_t>(splitter.bits.b0));
        for (int i = 1; i < 32; ++i) {
            if constexpr (i < sizeof...(Bits)) {
                result.push_back(static_cast<int8_t>(splitter.bits.b[i]));
            }
        }
        return result;
    } else if constexpr (sizeof(T) == 8) {
        BitSplitter64<T, Bits...> splitter(value);
        std::vector<int8_t> result;
        result.push_back(static_cast<int8_t>(splitter.bits.b0));
        for (int i = 1; i < 64; ++i) {
            if constexpr (i < sizeof...(Bits)) {
                result.push_back(static_cast<int8_t>(splitter.bits.b[i]));
            }
        }
        return result;
    } else {
        throw std::invalid_argument("Unsupported bit size");
    }
}

