#pragma once

#include <nxx/def.hpp>

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

constexpr char* strcpy(char* dest, const char* src)
{
    char* d = dest;
    while ((*d++ = *src++) != '\0');
    return dest;
}

constexpr char* strncpy(char* dest, const char* src, size_t len)
{
    char* d = dest;
    size_t i{0};
    for (; i < len && src[i] != '\0'; ++i)
    {
        d[i] = src[i];
    }
    for (; i < len; ++i)
    {
        d[i] = '\0';
    }
    return dest;
}

constexpr int strcmp(const char* lhs, const char* rhs)
{
    while (*lhs && (*lhs == *rhs))
    {
        ++lhs;
        ++rhs;
    }

    const char l = *lhs;
    const char r = *rhs;

    return static_cast<u8_t>(l) - static_cast<u8_t>(r);
}

constexpr int strncmp(const char* lhs, const char* rhs, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        if (lhs[i] != rhs[i] || lhs[i] == '\0' || rhs[i] == '\0')
        {
            return static_cast<u8_t>(lhs[i]) - static_cast<u8_t>(rhs[i]);
        }
    }
    return 0;
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
