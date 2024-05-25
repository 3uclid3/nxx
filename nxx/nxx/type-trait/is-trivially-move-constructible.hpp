#pragma once

namespace nxx {

template<typename T>
inline constexpr bool is_trivially_move_constructible = __is_trivially_move_constructible(T);

} // namespace nxx
