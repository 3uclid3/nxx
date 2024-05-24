#pragma once

#include <nxx/type-trait/details/is-same-impl.hpp>

namespace nxx {

template<typename T0, typename T1>
inline constexpr bool is_same = details::is_same_impl<T0, T1>::value;

} // namespace nxx
