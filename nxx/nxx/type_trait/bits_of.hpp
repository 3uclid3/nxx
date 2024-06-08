#pragma once

#include <nxx/def.hpp>
#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T>
struct bits_of : integral_constant<size_t, (sizeof(T) * bits_per_byte)>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr size_t bits_of = impl::bits_of<T>::value;

} // namespace nxx
