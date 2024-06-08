#pragma once

#include <nxx/def.hpp>

namespace nxx::impl {

template<typename T>
struct remove_all_extents
{
    using type = T;
};

template<typename T>
struct remove_all_extents<T[]>
{
    using type = typename remove_all_extents<T>::type;
};

template<typename T, size_t SizeT>
struct remove_all_extents<T[SizeT]>
{
    using type = typename remove_all_extents<T>::type;
};

} // namespace nxx::impl

namespace nxx {

template<typename T>
using remove_all_extents = typename impl::remove_all_extents<T>::type;

} // namespace nxx
