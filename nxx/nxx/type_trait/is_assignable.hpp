#pragma once

#include <nxx/type_trait/add_const.hpp>
#include <nxx/type_trait/add_lvalue_reference.hpp>
#include <nxx/type_trait/add_rvalue_reference.hpp>
#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T, typename U>
struct is_assignable : bool_constant<__is_assignable(T, U)>
{};

template<typename T>
struct is_copy_assignable : bool_constant<__is_assignable(typename add_lvalue_reference<T>::type, typename add_lvalue_reference<const T>::type)>
{};

template<typename T>
struct is_move_assignable : bool_constant<__is_assignable(typename add_lvalue_reference<T>::type, typename add_rvalue_reference<T>::type)>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T, typename U>
inline constexpr bool is_assignable = impl::is_assignable<T, U>::value;

template<typename T>
inline constexpr bool is_copy_assignable = impl::is_copy_assignable<T>::value;

template<typename T>
inline constexpr bool is_move_assignable = impl::is_move_assignable<T>::value;

} // namespace nxx
