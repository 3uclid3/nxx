#pragma once

#include <nxx/type_trait/add_rvalue_reference.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_copy_constructible = __is_assignable(T, add_lvalue_reference<T>);

} // namespace nxx
