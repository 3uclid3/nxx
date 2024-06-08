#pragma once

#include <nxx/type_trait/add_const.hpp>
#include <nxx/type_trait/add_lvalue_reference.hpp>
#include <nxx/type_trait/add_rvalue_reference.hpp>
#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T, typename... ArgsT>
struct is_constructible : bool_constant<__is_constructible(T, ArgsT...)>
{};

template<typename T>
struct is_copy_constructible : bool_constant<__is_constructible(T, typename add_lvalue_reference<const T>::type)>
{};

template<typename T>
struct is_move_constructible : bool_constant<__is_constructible(T, typename add_rvalue_reference<T>::type)>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T, typename U>
inline constexpr bool is_constructible = impl::is_constructible<T, U>::value;

template<typename T>
inline constexpr bool is_copy_constructible = impl::is_copy_constructible<T>::value;

template<typename T>
inline constexpr bool is_move_constructible = impl::is_move_constructible<T>::value;

} // namespace nxx
