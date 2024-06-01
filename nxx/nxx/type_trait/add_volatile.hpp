#pragma once

#include <nxx/type_trait/details/add_volatile_impl.hpp>

namespace nxx {

template<typename T>
using add_volatile = details::add_volatile_impl<T>::type;

} // namespace nxx
