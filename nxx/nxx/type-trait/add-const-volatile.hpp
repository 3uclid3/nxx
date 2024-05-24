#pragma once

#include <nxx/type-trait/details/add-const-volatile-impl.hpp>

namespace nxx {

template<typename T>
using add_const_volatile = details::add_const_volatile_impl<T>::type;

} // namespace nxx
