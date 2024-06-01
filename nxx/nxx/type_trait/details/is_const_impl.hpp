#pragma once

#include <nxx/type_trait/integral_constant.hpp>
#include <nxx/def.hpp>

namespace nxx::details {

template<typename T>
struct is_const_impl : false_type
{};

template<typename T>
struct is_const_impl<const T> : true_type
{};

} // namespace nxx::details
