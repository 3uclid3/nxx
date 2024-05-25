#pragma once

#include <nxx/type-trait/is-enum.hpp>

namespace nxx::details {

template<typename T, bool = is_enum<T>>
struct underlying_type_impl;

template<typename T>
struct underlying_type_impl<T, false>
{
};

template<typename T>
struct underlying_type_impl<T, true>
{
    using type = __underlying_type(T);
};

} // namespace nxx::details
