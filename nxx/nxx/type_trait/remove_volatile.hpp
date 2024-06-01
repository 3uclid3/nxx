#pragma once

#include <nxx/type_trait/details/remove_volatile_impl.hpp>

namespace nxx {

template<typename T>
using remove_volatile = details::remove_volatile_impl<T>::type;

} // namespace nxx
