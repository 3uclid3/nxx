#pragma once

namespace nxx {

template<typename T>
inline constexpr bool is_trivially_copyable = __is_trivially_copyable(T);

} // namespace nxx
