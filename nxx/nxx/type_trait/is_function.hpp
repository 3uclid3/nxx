#pragma once

#include <nxx/type_trait/integral_constant.hpp>
#include <nxx/type_trait/is_const.hpp>
#include <nxx/type_trait/is_reference.hpp>

namespace nxx::impl {

template<typename T>
struct is_function : bool_constant<!(is_reference<T>::value || is_const<const T>::value)>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_function = impl::is_function<T>::value;

} // namespace nxx
