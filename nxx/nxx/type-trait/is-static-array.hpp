#pragma once

#include <nxx/type-trait/details/is-static-array-impl.hpp>

namespace nxx {

template<typename T>
constexpr bool is_static_array = details::is_static_array_impl<T>::value;

} // namespace nxx
