#pragma once

#include <nxx/type-trait/add-rvalue-reference.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_copy_constructible = __is_assignable(T, add_lvalue_reference<T>);

} // namespace nxx
