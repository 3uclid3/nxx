#pragma once

#include <nxx/type_trait/details/is_integral_impl.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_integral = details::is_integral_impl<T>::value;

} // namespace nxx
