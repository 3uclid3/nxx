#pragma once

#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T>
struct is_trivially_copyable : bool_constant<__is_trivially_copyable(T)>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_trivially_copyable = impl::is_trivially_copyable<T>::value;

} // namespace nxx
