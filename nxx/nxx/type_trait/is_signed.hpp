#pragma once

#include <nxx/type_trait/details/is_signed_impl.hpp>

namespace nxx {

template<typename T>
inline constexpr bool is_signed = details::is_signed_impl<T>::value;

} // namespace nxx
