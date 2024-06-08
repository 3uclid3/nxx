#pragma once

#include <nxx/type_trait/is_enum.hpp>

namespace nxx::impl {

template<typename T, bool = is_enum<T>::value>
struct underlying_type;

template<typename T>
struct underlying_type<T, false>
{};

template<typename T>
struct underlying_type<T, true>
{
    using type = __underlying_type(T);
};

} // namespace nxx::impl

namespace nxx {

template<typename T>
using underlying_type = impl::underlying_type<T>::type;

} // namespace nxx
