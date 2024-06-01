#pragma once

#include <nxx/type_trait/details/is_signed_integer_impl.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_signed_integer = details::is_signed_integer_impl<T>::value;

} // namespace nxx
