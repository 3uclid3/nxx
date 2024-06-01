#pragma once

#include <nxx/type_trait/integral_constant.hpp>
#include <nxx/type_trait/is_arithmetic.hpp>
#include <nxx/type_trait/is_integral.hpp>

namespace nxx::details {

template<typename T, bool = is_integral<T>>
struct is_signed_base_impl : public bool_constant<(T(-1) < T(0))>
{};

template<typename T>
struct is_signed_base_impl<T, false> : true_type
{}; // floating point

template<typename T, bool = is_arithmetic<T>>
struct is_signed_impl : is_signed_base_impl<T>
{};

template<class T>
struct is_signed_impl<T, false> : false_type
{};

} // namespace nxx::details