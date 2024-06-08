#pragma once

#include <nxx/type_trait/integral_constant.hpp>
#include <nxx/type_trait/is_floating_point.hpp>
#include <nxx/type_trait/is_integral.hpp>

namespace nxx::impl {

template<typename T>
struct is_arithmetic : bool_constant<is_integral<T>::value || is_floating_point<T>::value>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_arithmetic = impl::is_arithmetic<T>::value;

} // namespace nxx
