#pragma once

#include <nxx/type_trait/integral_constant.hpp>
#include <nxx/def.hpp>

namespace nxx::details {

template<typename T>
struct is_integral_impl : false_type
{};

template<> struct is_integral_impl<bool> : true_type {};
template<> struct is_integral_impl<char> : true_type {};
template<> struct is_integral_impl<u8_t> : true_type {};
template<> struct is_integral_impl<s8_t> : true_type {};
template<> struct is_integral_impl<u16_t> : true_type {};
template<> struct is_integral_impl<s16_t> : true_type {};
template<> struct is_integral_impl<u32_t> : true_type {};
template<> struct is_integral_impl<s32_t> : true_type {};
template<> struct is_integral_impl<u64_t> : true_type {};
template<> struct is_integral_impl<s64_t> : true_type {};

} // namespace nxx::details
