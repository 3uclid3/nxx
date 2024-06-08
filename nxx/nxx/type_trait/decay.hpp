#pragma once

#include <nxx/type_trait/add_pointer.hpp>
#include <nxx/type_trait/conditional.hpp>
#include <nxx/type_trait/is_array.hpp>
#include <nxx/type_trait/is_function.hpp>
#include <nxx/type_trait/is_referenceable.hpp>
#include <nxx/type_trait/remove_cv.hpp>
#include <nxx/type_trait/remove_extent.hpp>
#include <nxx/type_trait/remove_reference.hpp>

namespace nxx::impl {

template<class T, bool>
struct decay_impl
{
    using type = typename remove_cv<T>::type;
};

template<class T>
struct decay_impl<T, true>
{
    using type = typename conditional<
        is_array<T>::value,
        typename add_pointer<typename remove_extent<T>::type>::type,
        typename conditional<is_function<T>::value, typename add_pointer<T>::type, typename remove_cv<T>::type>::type>::type;
};

template<typename T>
struct decay
{
    using type = typename decay_impl<
        typename remove_reference<T>::type, 
        is_referenceable<typename remove_reference<T>::type>::value
    >::type;
};

} // namespace nxx::impl

namespace nxx {

template<typename T>
using decay = impl::decay<T>::type;

} // namespace nxx