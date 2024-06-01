#pragma once

namespace nxx {

template<typename T>
inline constexpr bool is_lvalue_reference = __is_lvalue_reference(T);

} // namespace nxx
