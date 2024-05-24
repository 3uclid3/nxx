#pragma once

#include <nxx/type-trait/details/is-floating-point-impl.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_floating_point = details::is_floating_point_impl<T>::value;

} // namespace nxx
