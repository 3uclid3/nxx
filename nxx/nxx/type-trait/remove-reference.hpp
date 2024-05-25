#pragma once

#include <nxx/type-trait/details/remove-reference-impl.hpp>

namespace nxx {

template<typename T>
using remove_reference = details::remove_reference_impl<T>::type;

} // namespace nxx
