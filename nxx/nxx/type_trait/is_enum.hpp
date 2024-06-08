#pragma once

#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T>
struct is_enum : bool_constant<__is_enum(T)>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_enum = impl::is_enum<T>::value;

} // namespace nxx
