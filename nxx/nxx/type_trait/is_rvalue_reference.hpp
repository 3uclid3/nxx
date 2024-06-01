#pragma once

namespace nxx {

template<typename T>
inline constexpr bool is_rvalue_reference = __is_rvalue_reference(T);

} // namespace nxx
