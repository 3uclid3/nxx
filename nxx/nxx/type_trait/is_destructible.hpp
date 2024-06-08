#pragma once

#include <nxx/type_trait/integral_constant.hpp>
#include <nxx/type_trait/is_function.hpp>
#include <nxx/type_trait/is_reference.hpp>
#include <nxx/type_trait/remove_all_extents.hpp>
#include <nxx/utility/declval.hpp>

namespace nxx::impl {

//  if it's a reference, return true
//  if it's a function, return false
//  if it's void, return false
//  if it's an array of unknown bound, return false
//  Otherwise, return "declval<Up&>().~Up()" is well-formed
//    where Up is remove_all_extents<Tp>::type

template<typename>
struct is_destructible_apply
{
    using type = int;
};

template<typename T>
struct is_destructor_wellformed
{
    template<typename T1>
    static true_type test(typename is_destructible_apply<decltype(declval<T1&>().~T1())>::type);

    template<typename T1>
    static false_type test(...);

    static const bool value = decltype(test<T>(42))::value;
};

template<typename T, bool>
struct destructible;

template<typename T>
struct destructible<T, false> : bool_constant<is_destructor_wellformed<typename remove_all_extents<T>::type>::value>
{};

template<typename T>
struct destructible<T, true> : true_type
{};

template<typename T, bool>
struct destructible_false;

template<typename T>
struct destructible_false<T, false> : destructible<T, is_reference<T>::value>
{};

template<typename T>
struct destructible_false<T, true> : public false_type
{};

template<typename T>
struct is_destructible : public destructible_false<T, is_function<T>::value>
{};

template<typename T>
struct is_destructible<T[]> : public false_type
{};

template<>
struct is_destructible<void> : public false_type
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_destructible = impl::is_destructible<T>::value;

} // namespace nxx
