#pragma once

namespace nxx {

template<typename T>
inline constexpr bool is_trivially_destructible = __is_trivially_destructible(T);

} // namespace nxx
