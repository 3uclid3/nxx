#pragma once

#include <nxx/def.hpp>

namespace nxx {

// TODO move to cpp
inline void* memset(void* ptr, int val, size_t size)
{
    const u8_t uval = static_cast<u8_t>(val);
    u8_t* p = reinterpret_cast<u8_t*>(ptr);
    for (size_t i = 0; i < size; ++i)
    {
        p[i] = uval;
    }
    return ptr;
}

inline void* memcpy(void* dest, const void* src, size_t size)
{
    u8_t* d = reinterpret_cast<u8_t*>(dest);
    const u8_t* s = reinterpret_cast<const u8_t*>(src);
    for (size_t i = 0; i < size; ++i)
    {
        d[i] = s[i];
    }
    return dest;
}

constexpr size_t strlen(const char* cstr)
{
    size_t size{0};
    if (cstr != nullptr)
    {
        while (cstr[size] != '\0') ++size;
    }
    return size;
}

constexpr bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

constexpr u8_t to_digit(char c)
{
    return static_cast<u8_t>(c - '0');
}

} // namespace nxx
