#pragma once

#include <cstdint>

template <class T, size_t N>
struct Array {
    T x[N];

    constexpr T& operator[](uint32_t index) {
        return x[index];
    }

    template <class ...Args>
    constexpr Array(const Args&... args) : x{args...}
    {
    }
};