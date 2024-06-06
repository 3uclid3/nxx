#pragma once

#include <nxx/type_trait/add_const.hpp>
#include <nxx/type_trait/add_rvalue_reference.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_copy_constructible = __is_constructible(T, add_lvalue_reference<add_const<T>>);

} // namespace nxx
