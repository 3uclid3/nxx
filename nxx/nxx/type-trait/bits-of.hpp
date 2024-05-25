#pragma once

#include <nxx/type-trait/details/bits-of-impl.hpp>

namespace nxx {

template<typename T>
inline constexpr size_t bits_of = details::bits_of_impl<T>::value;

} // namespace nxx