#pragma once

#include <nxx/type_trait/add_rvalue_reference.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_trivially_move_constructible = __is_trivially_constructible(T, add_rvalue_reference<T>);

} // namespace nxx
