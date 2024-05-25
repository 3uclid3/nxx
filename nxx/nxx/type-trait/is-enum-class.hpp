#pragma once

#include <nxx/type-trait/details/is-enum-class-impl.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_enum_class = details::is_enum_class_impl<T>::value;

} // namespace nxx
