#pragma once

#include <nxx/type_trait/remove_const.hpp>
#include <nxx/type_trait/remove_volatile.hpp>

namespace nxx {

template<typename T>
using remove_const_volatile = remove_const<remove_volatile<T>>;

} // namespace nxx
