#pragma once

#include <nxx/def.hpp>
#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T>
struct is_array : public false_type
{};

template<typename T>
struct is_array<T[]> : public true_type
{};

template<typename T, size_t SizeT>
struct is_array<T[SizeT]> : public true_type
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_array = impl::is_array<T>::value;

} // namespace nxx
