#pragma once

namespace nxx::impl {

template<typename T>
struct add_volatile
{
    using type = volatile T;
};

} // namespace nxx::impl

namespace nxx {

template<typename T>
using add_volatile = impl::add_volatile<T>::type;

} // namespace nxx
