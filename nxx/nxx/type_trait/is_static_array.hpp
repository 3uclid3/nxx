#pragma once

#include <nxx/container/static_array.hpp>
#include <nxx/def.hpp>
#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T>
struct is_static_array : false_type
{};

template<typename T, size_t SizeT>
struct is_static_array<static_array<T, SizeT>> : true_type
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
constexpr bool is_static_array = impl::is_static_array<T>::value;

} // namespace nxx
