#pragma once

#include <nxx/type_trait/remove_const.hpp>
#include <nxx/type_trait/remove_volatile.hpp>

namespace nxx::impl {

template<typename T>
struct remove_cv
{
    using type = typename remove_const<typename remove_volatile<T>::type>::type;
};

} // namespace nxx::impl

namespace nxx {

template<typename T>
using remove_cv = typename impl::remove_cv<T>::type;

} // namespace nxx
