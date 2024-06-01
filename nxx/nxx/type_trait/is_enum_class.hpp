#pragma once

#include <nxx/type_trait/details/is_enum_class_impl.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_enum_class = details::is_enum_class_impl<T>::value;

} // namespace nxx
