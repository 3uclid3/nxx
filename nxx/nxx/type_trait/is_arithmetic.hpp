#pragma once

#include <nxx/type_trait/is_floating_point.hpp>
#include <nxx/type_trait/is_integral.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_arithmetic = is_integral<T> || is_floating_point<T>;

} // namespace nxx
