#pragma once

#include <nxx/type_trait/add_lvalue_reference.hpp>
#include <nxx/type_trait/add_rvalue_reference.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_copy_assignable = __is_assignable(add_lvalue_reference<T>, add_lvalue_reference<T>);

} // namespace nxx
