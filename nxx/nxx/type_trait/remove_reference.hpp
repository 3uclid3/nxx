#pragma once

#include <nxx/type_trait/details/remove_reference_impl.hpp>

namespace nxx {

template<typename T>
using remove_reference = details::remove_reference_impl<T>::type;

} // namespace nxx
