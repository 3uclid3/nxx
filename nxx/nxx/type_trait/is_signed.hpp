#pragma once

#include <nxx/type_trait/integral_constant.hpp>
#include <nxx/type_trait/is_arithmetic.hpp>
#include <nxx/type_trait/is_integral.hpp>

namespace nxx::impl {

template<typename T, bool = is_integral<T>::value>
struct is_signed_base : public bool_constant<(T(-1) < T(0))>
{};

template<typename T>
struct is_signed_base<T, false> : true_type
{}; // floating point

template<typename T, bool = is_arithmetic<T>::value>
struct is_signed : is_signed_base<T>
{};

template<class T>
struct is_signed<T, false> : false_type
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_signed = impl::is_signed<T>::value;

} // namespace nxx
