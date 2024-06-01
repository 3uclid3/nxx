#pragma once

#include <nxx/type_trait/integral_constant.hpp>
#include <nxx/type_trait/is_convertible.hpp>
#include <nxx/type_trait/is_enum.hpp>
#include <nxx/type_trait/underlying_type.hpp>

namespace nxx::details {

template<typename T, bool = is_enum<T>>
struct is_enum_class_impl;

template<typename T>
struct is_enum_class_impl<T, false> : false_type
{};

template<typename T>
struct is_enum_class_impl<T, true> : bool_constant<!is_convertible<T, underlying_type<T>>>
{
};

} // namespace Details