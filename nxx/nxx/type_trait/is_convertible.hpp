#pragma once

#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename FromT, typename ToT>
struct is_convertible : bool_constant<__is_convertible(FromT, ToT)>
{};

} // namespace nxx::impl

namespace nxx {

template<typename FromT, typename ToT>
inline constexpr bool is_convertible = impl::is_convertible<FromT, ToT>::value;

} // namespace nxx
