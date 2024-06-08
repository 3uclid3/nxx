#pragma once

#include <nxx/type_trait/add_const.hpp>
#include <nxx/type_trait/add_lvalue_reference.hpp>
#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T, typename... ArgsT>
struct is_trivially_constructible : bool_constant<__is_trivially_constructible(T, ArgsT...)>
{};

template<typename T>
struct is_trivially_copy_constructible : bool_constant<__is_trivially_constructible(T, typename add_lvalue_reference<const T>::type)>
{};

template<typename T>
struct is_trivially_move_constructible : bool_constant<__is_trivially_constructible(T, typename add_rvalue_reference<T>::type)>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T, typename... ArgsT>
inline constexpr bool is_trivially_constructible = impl::is_trivially_constructible<T, ArgsT...>::value;

template<typename T>
inline constexpr bool is_trivially_copy_constructible = impl::is_trivially_copy_constructible<T>::value;

template<typename T>
inline constexpr bool is_trivially_move_constructible = impl::is_trivially_move_constructible<T>::value;

} // namespace nxx
