#pragma once

#include <nxx/type_trait/add_const.hpp>
#include <nxx/type_trait/add_lvalue_reference.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_copy_assignable = __is_assignable(add_lvalue_reference<T>, add_lvalue_reference<add_const<T>>);

} // namespace nxx
