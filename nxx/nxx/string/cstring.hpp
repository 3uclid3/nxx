#pragma once

#include <stddef.h>

namespace nxx {

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
