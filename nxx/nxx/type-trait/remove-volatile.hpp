#pragma once

#include <nxx/type-trait/details/remove-volatile-impl.hpp>

namespace nxx {

template<typename T>
using remove_volatile = details::remove_volatile_impl<T>::type;

} // namespace nxx
