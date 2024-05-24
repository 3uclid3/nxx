#pragma once

#include <nxx/type-trait/details/add-const-impl.hpp>

namespace nxx {

template<typename T>
using add_const = details::add_const_impl<T>::type;

} // namespace nxx
