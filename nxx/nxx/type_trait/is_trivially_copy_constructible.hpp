#pragma once

namespace nxx {

template<typename T>
inline constexpr bool is_trivially_copy_constructible = __is_trivially_copy_constructible(T);

} // namespace nxx
