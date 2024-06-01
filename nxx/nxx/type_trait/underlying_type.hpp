#pragma once

#include <nxx/type_trait/details/underlying_type_impl.hpp>

namespace nxx {

template<typename T>
using underlying_type = details::underlying_type_impl<T>::type;

} // namespace nxx
