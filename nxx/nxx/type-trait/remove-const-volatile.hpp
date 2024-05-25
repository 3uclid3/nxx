#pragma once

#include <nxx/type-trait/remove-const.hpp>
#include <nxx/type-trait/remove-volatile.hpp>

namespace nxx {

template<typename T>
using add_const_volatile = remove_const<remove_volatile<T>>;

} // namespace nxx
