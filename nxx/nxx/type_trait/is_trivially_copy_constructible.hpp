#pragma once

#include <nxx/type_trait/add_const.hpp>
#include <nxx/type_trait/add_lvalue_reference.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_trivially_copy_constructible = __is_trivially_constructible(T, add_lvalue_reference<add_const<T>>);

} // namespace nxx
