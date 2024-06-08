#pragma once

#include <nxx/type_trait/add_const.hpp>
#include <nxx/type_trait/add_volatile.hpp>

namespace nxx {

template<typename T>
using add_cv = add_const<add_volatile<T>>;

} // namespace nxx
