#pragma once

#include <nxx/type_trait/details/add_const_impl.hpp>

namespace nxx {

template<typename T>
using add_const = details::add_const_impl<T>::type;

} // namespace nxx
