#pragma once

#include <nxx/def.hpp>
#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T>
struct is_const : false_type
{};

template<typename T>
struct is_const<const T> : true_type
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_const = impl::is_const<T>::value;

} // namespace nxx
