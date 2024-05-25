#pragma once

namespace nxx {

template<typename FromT, typename ToT>
inline constexpr bool is_convertible = __is_convertible(FromT, ToT);

} // namespace NOS