#pragma once

#include <nxx/type-trait/details/is-integral-impl.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_integral = details::is_integral_impl<T>::value;

} // namespace nxx
