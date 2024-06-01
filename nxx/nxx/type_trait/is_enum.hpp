#pragma once

namespace nxx {

template<typename T>
inline constexpr bool is_enum = __is_enum(T);

} // namespace nxx
