#pragma once

namespace nxx {

template<typename T>
inline constexpr bool is_function = __is_function(T);

} // namespace nxx
