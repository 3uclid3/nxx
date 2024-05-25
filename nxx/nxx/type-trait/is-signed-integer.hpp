#pragma once

#include <nxx/type-trait/details/is-signed-integer-impl.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_signed_integer = details::is_signed_integer_impl<T>::value;

} // namespace nxx
