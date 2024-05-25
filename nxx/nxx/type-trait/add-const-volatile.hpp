#pragma once

#include <nxx/type-trait/add-const.hpp>
#include <nxx/type-trait/add-volatile.hpp>

namespace nxx {

template<typename T>
using add_const_volatile = add_const<add_volatile<T>>;

} // namespace nxx
