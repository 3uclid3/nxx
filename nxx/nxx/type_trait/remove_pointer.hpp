#pragma once

#include <nxx/type_trait/details/remove_pointer_impl.hpp>

namespace nxx {

template<typename T>
using remove_pointer = details::remove_pointer_impl<T>::type;

} // namespace nxx
