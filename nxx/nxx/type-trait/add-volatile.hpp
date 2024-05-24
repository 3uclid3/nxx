#pragma once

#include <nxx/type-trait/details/add-volatile-impl.hpp>

namespace nxx {

template<typename T>
using add_volatile = details::add_volatile_impl<T>::type;

} // namespace nxx
