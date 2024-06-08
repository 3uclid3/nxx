#pragma once

namespace nxx::impl {

template<typename T>
struct remove_pointer
{
    using type = T;
};

template<typename T>
struct remove_pointer<T*>
{
    using type = T;
};

} // namespace nxx::impl

namespace nxx {

template<typename T>
using remove_pointer = impl::remove_pointer<T>::type;

} // namespace nxx
