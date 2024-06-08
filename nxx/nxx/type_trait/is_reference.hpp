#pragma once

#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T>
struct is_lvalue_reference : false_type
{};
template<typename T>
struct is_lvalue_reference<T&> : true_type
{};

template<typename T>
struct is_rvalue_reference : false_type
{};
template<typename T>
struct is_rvalue_reference<T&&> : true_type
{};

template<typename T>
struct is_reference : bool_constant<is_lvalue_reference<T>::value || is_rvalue_reference<T>::value>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_lvalue_reference = impl::is_lvalue_reference<T>::value;

template<typename T>
inline constexpr bool is_rvalue_reference = impl::is_lvalue_reference<T>::value;

template<typename T>
inline constexpr bool is_reference = impl::is_lvalue_reference<T>::value;

} // namespace nxx
