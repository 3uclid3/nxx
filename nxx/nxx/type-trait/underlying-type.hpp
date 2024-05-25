#pragma once

#include <nxx/type-trait/details/underlying-type-impl.hpp>

namespace nxx {

template<typename T>
using underlying_type = details::underlying_type_impl<T>::type;

} // namespace nxx
