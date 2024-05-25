#pragma once

namespace nxx {

template<typename T>
inline constexpr bool is_reference = __is_reference(T);

} // namespace nxx
