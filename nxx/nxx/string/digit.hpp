#pragma once

#include <nxx/def.hpp>

namespace nxx {

constexpr bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

constexpr u8_t to_digit(char c)
{
    return static_cast<u8_t>(c - '0');
}

} // namespace nxx
