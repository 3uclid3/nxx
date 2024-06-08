#pragma once

#include <nxx/def.hpp>
#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T>
struct is_signed_integer : false_type
{};

// clang-format off
template<> struct is_signed_integer<s8_t> : true_type { };
template<> struct is_signed_integer<s16_t> : true_type { };
template<> struct is_signed_integer<s32_t> : true_type { };
template<> struct is_signed_integer<s64_t> : true_type { };
// clang-format on

} // namespace nxx::details

namespace nxx {

template<typename T>
inline constexpr bool is_signed_integer = impl::is_signed_integer<T>::value;

} // namespace nxx
