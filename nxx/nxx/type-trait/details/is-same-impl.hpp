#pragma once

#include <nxx/type-trait/integral-constant.hpp>

namespace nxx::details {

template<typename T0, typename T1>
struct is_same_impl : false_type
{
};

template<typename T>
struct is_same_impl<T, T> : true_type
{
};

} // namespace nxx::details
