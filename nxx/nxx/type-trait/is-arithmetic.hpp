#pragma once

#include <nxx/type-trait/is-floating-point.hpp>
#include <nxx/type-trait/is-integral.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_arithmetic = is_integral<T> || is_floating_point<T>;

} // namespace nxx
