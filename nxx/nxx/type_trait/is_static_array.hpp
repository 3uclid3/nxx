#pragma once

#include <nxx/type_trait/details/is_static_array_impl.hpp>

namespace nxx {

template<typename T>
constexpr bool is_static_array = details::is_static_array_impl<T>::value;

} // namespace nxx
