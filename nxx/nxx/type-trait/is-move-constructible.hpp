#pragma once

#include <nxx/type-trait/add-rvalue-reference.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_move_constructible = __is_assignable(T, add_rvalue_reference<T>);

} // namespace nxx
