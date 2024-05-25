#pragma once

#include <nxx/type-trait/details/is-const-impl.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_const = details::is_const_impl<T>::value;

} // namespace nxx
