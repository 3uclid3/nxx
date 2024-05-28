#pragma once

namespace nxx {

template<typename T>
constexpr T max(T lhs, T rhs);

template<typename T>
constexpr T max(T lhs, T rhs)
{
    return lhs < rhs ? rhs : lhs;
}

} // namespace nxx
