#pragma once

#include <nxx/type_trait/is_referenceable.hpp>

namespace nxx::impl {

template<typename T, bool = is_referenceable<T>::value>
struct add_rvalue_reference
{
    using type = T;
};

template<class T>
struct add_rvalue_reference<T, true>
{
    using type = T&&;
};

} // namespace nxx::impl

namespace nxx {

template<typename T>
using add_rvalue_reference = typename impl::add_rvalue_reference<T>::type;

} // namespace nxx
