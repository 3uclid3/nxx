#pragma once

#include <nxx/type-trait/add-const.hpp>
#include <nxx/type-trait/add-volatile.hpp>

namespace nxx::details {

template<class T>
struct add_const_volatile_impl
{
    using type = add_const<add_volatile<T>>;
};

} // namespace nxx::details
