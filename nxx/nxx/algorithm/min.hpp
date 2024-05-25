#pragma once

namespace nxx {

template<typename T>
constexpr T min(T lhs, T rhs);

template<typename T>
constexpr T min(T lhs, T rhs)
{
    return lhs > rhs ? rhs : lhs;
}

} // namespace NOS