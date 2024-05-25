#pragma once

#include <nxx/def.hpp>
#include <nxx/type-trait/integral-constant.hpp>

namespace nxx::details {

template<typename T>
struct bits_of_impl : integral_constant<size_t, (sizeof(T) * bits_per_byte)>
{
};

} // namespace nxx