#pragma once

#include <nxx/type_trait/is_referenceable.hpp>
#include <nxx/type_trait/is_void.hpp>
#include <nxx/type_trait/remove_reference.hpp>

namespace nxx::impl {

template<typename T, bool = is_referenceable<T>::value || is_void<T>::value>
struct add_pointer
{
    using type = typename remove_reference<T>::type*;
};

template<typename T>
struct add_pointer<T, false>
{
    using type = T;
};

} // namespace nxx::impl

namespace nxx {

template<typename T>
using add_pointer = typename impl::add_pointer<T>::type;

} // namespace nxx
