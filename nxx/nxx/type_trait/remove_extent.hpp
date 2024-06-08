#pragma once

#include <nxx/def.hpp>

namespace nxx::impl {

template<typename T>
struct remove_extent
{
    using type = T;
};
template<typename T>
struct remove_extent<T[]>
{
    using type = T;
};
template<typename T, size_t SizeT>
struct remove_extent<T[SizeT]>
{
    using type = T;
};

} // namespace nxx::impl

namespace nxx {

template<typename T>
using remove_extent_t = typename impl::remove_extent<T>::type;

} // namespace nxx
