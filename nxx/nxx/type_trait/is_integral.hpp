#pragma once

#include <nxx/def.hpp>
#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

// clang-format off
template<typename T>
struct is_integral : false_type {};

template<> struct is_integral<bool> : true_type {};
template<> struct is_integral<char> : true_type {};
template<> struct is_integral<u8_t> : true_type {};
template<> struct is_integral<s8_t> : true_type {};
template<> struct is_integral<u16_t> : true_type {};
template<> struct is_integral<s16_t> : true_type {};
template<> struct is_integral<u32_t> : true_type {};
template<> struct is_integral<s32_t> : true_type {};
template<> struct is_integral<u64_t> : true_type {};
template<> struct is_integral<s64_t> : true_type {};
// clang-format on

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_integral = impl::is_integral<T>::value;

} // namespace nxx
