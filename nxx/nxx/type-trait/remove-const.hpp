#pragma once

#include <nxx/type-trait/details/remove-const-impl.hpp>

namespace nxx {

template<typename T>
using remove_const = details::remove_const_impl<T>::type;

} // namespace nxx
