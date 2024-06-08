#pragma once

#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T>
struct is_trivially_assignable : bool_constant<__is_trivially_assignable(T)>
{};

template<typename T>
struct is_trivially_copy_assignable : bool_constant<__is_trivially_copy_assignable(T)>
{};

template<typename T>
struct is_trivially_move_assignable : bool_constant<__is_trivially_move_assignable(T)>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_trivially_assignable = impl::is_trivially_assignable<T>::value;

template<typename T>
inline constexpr bool is_trivially_copy_assignable = impl::is_trivially_copy_assignable<T>::value;

template<typename T>
inline constexpr bool is_trivially_move_assignable = impl::is_trivially_move_assignable<T>::value;

} // namespace nxx
