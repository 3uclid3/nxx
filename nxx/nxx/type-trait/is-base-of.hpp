#pragma once

namespace nxx {

template<typename BaseT, typename DerivedT>
inline constexpr bool is_base_of = __is_base_of(BaseT, DerivedT);

} // namespace nxx
