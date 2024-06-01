#pragma once

namespace nxx {

template<typename T>
constexpr T* address_of(T& x)
{
    return __builtin_addressof(x);
}

template<typename T>
constexpr T* address_of(const T&&) = delete;

} // namespace nxx
