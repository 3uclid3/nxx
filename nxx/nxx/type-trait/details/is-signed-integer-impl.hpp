#pragma once

#include <nxx/def.hpp>
#include <nxx/type-trait/integral-constant.hpp>

namespace nxx::details {

template<typename T>
struct is_signed_integer_impl : false_type
{
};

template<> struct is_signed_integer_impl<s8_t> : true_type { };
template<> struct is_signed_integer_impl<s16_t> : true_type { };
template<> struct is_signed_integer_impl<s32_t> : true_type { };
template<> struct is_signed_integer_impl<s64_t> : true_type { };

} // namespace nxx::details
