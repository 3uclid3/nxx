#pragma once

namespace nxx {

template<typename T>
inline constexpr bool is_trivially_copy_assignable = __is_trivially_copy_assignable(T);

} // namespace nxx
