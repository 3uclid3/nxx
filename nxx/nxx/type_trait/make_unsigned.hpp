#pragma once

#include <nxx/type_trait/is_enum.hpp>
#include <nxx/type_trait/is_integral.hpp>
#include <nxx/type_trait/copy_const_volatile.hpp>
#include <nxx/type_trait/remove_const_volatile.hpp>

namespace nxx {

namespace details {

template<typename T, bool = is_integral<T> || is_enum<T>>
struct make_unsigned_impl
{};

// clang-format off
template <> struct make_unsigned_impl<bool, true> {};
template <> struct make_unsigned_impl<s8_t, true> { using type = u8_t; };
template <> struct make_unsigned_impl<u8_t, true> { using type = u8_t; };
template <> struct make_unsigned_impl<s16_t, true> { using type = u16_t; };
template <> struct make_unsigned_impl<u16_t, true> { using type = u16_t; };
template <> struct make_unsigned_impl<s32_t, true> { using type = u32_t; };
template <> struct make_unsigned_impl<u32_t, true> { using type = u32_t; };
template <> struct make_unsigned_impl<s64_t, true> { using type = u64_t; };
template <> struct make_unsigned_impl<u64_t, true> { using type = u64_t; };
// clang-format on

} // namespace details

template<class T>
using make_unsigned = copy_const_volatile<T, typename details::make_unsigned_impl<remove_const_volatile<T>>::type>;

} // namespace nxx
