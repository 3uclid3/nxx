#pragma once

namespace nxx::impl {

template<class T>
struct add_const
{
    using type = const T;
};

} // namespace nxx::impl

namespace nxx {

template<typename T>
using add_const = impl::add_const<T>::type;

} // namespace nxx
