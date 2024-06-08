#pragma once

#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T>
struct is_trivial : bool_constant<__is_trivial(T)>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_trivial = impl::is_trivial<T>::value;

} // namespace nxx
