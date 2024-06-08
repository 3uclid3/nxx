#pragma once

namespace nxx::impl {

template<typename T>
struct remove_volatile
{
    using type = T;
};

template<typename T>
struct remove_volatile<volatile T>
{
    using type = T;
};

} // namespace nxx::impl

namespace nxx {

template<typename T>
using remove_volatile = impl::remove_volatile<T>::type;

} // namespace nxx
