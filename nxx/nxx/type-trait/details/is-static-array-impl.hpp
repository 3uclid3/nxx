#pragma once

#include <nxx/container/static-array.hpp>
#include <nxx/def.hpp>
#include <nxx/type-trait/integral-constant.hpp>

namespace nxx::details {

template<typename T>
struct is_static_array_impl : false_type
{};

template<typename T, size_t SizeT>
struct is_static_array_impl<static_array<T, SizeT>> : true_type
{};

} // namespace nxx::details
