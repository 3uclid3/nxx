#pragma once

namespace nxx::impl {

template<typename T>
struct remove_const
{
    using type = T;
};

template<typename T>
struct remove_const<const T>
{
    using type = T;
};

} // namespace nxx::details

namespace nxx {

template<typename T>
using remove_const = impl::remove_const<T>::type;

} // namespace nxx
