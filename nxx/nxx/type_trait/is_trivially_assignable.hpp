#pragma once

namespace nxx {

template<typename T>
inline constexpr bool is_trivially_assignable = __is_trivially_assignable(T);

} // namespace nxx
