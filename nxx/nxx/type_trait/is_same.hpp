#pragma once

#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T0, typename T1>
struct is_same : false_type
{};

template<typename T>
struct is_same<T, T> : true_type
{};

template<typename T0, typename T1>
struct is_not_same : bool_constant<!is_same<T0, T1>::value> 
{};

} // namespace nxx::impl

namespace nxx {

template<typename T0, typename T1>
inline constexpr bool is_same = impl::is_same<T0, T1>::value;

template<typename T0, typename T1>
inline constexpr bool is_not_same = impl::is_not_same<T0, T1>::value;

} // namespace nxx
