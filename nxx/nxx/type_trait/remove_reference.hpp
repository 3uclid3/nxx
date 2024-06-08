#pragma once

namespace nxx::impl {

template<typename T>
struct remove_reference
{
    using type = T;
};

template<typename T>
struct remove_reference<T&>
{
    using type = T;
};

template<typename T>
struct remove_reference<T&&>
{
    using type = T;
};

} // namespace nxx::impl

namespace nxx {

template<typename T>
using remove_reference = impl::remove_reference<T>::type;

} // namespace nxx
