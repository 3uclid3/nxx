#pragma once

#include <nxx/type_trait/integral_constant.hpp>
#include <nxx/type_trait/is_destructible.hpp>

namespace nxx::impl {

#if __has_builtin(__is_trivially_destructible)

template<typename T>
struct is_trivially_destructible : bool_constant<__is_trivially_destructible(T)>
{};

#elif __has_builtin(__has_trivial_destructor)

template<typename T>
struct is_trivially_destructible : bool_constant<is_destructible<T>::value&& __has_trivial_destructor(T)>
{};

#else

#error is_trivially_destructible is not implemented

#endif // __has_builtin(__is_trivially_destructible)

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_trivially_destructible = impl::is_trivially_destructible<T>::value;

} // namespace nxx
