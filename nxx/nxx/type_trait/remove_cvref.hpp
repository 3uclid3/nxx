#pragma once

#include <nxx/type_trait/remove_cv.hpp>
#include <nxx/type_trait/remove_reference.hpp>

namespace nxx::impl {

template<typename T>
struct remove_cvref
{
    using type = typename remove_cv<typename remove_reference<T>::type>::type;
};

} // namespace nxx::impl

namespace nxx {

template<typename T>
using remove_cvref = typename impl::remove_cvref<T>::type;

} // namespace nxx
