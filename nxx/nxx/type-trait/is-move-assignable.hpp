#pragma once

#include <nxx/type-trait/add-lvalue-reference.hpp>
#include <nxx/type-trait/add-rvalue-reference.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_move_assignable = __is_assignable(add_lvalue_reference<T>, add_rvalue_reference<T>);

} // namespace nxx
