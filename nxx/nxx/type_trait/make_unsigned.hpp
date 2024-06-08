#pragma once

#include <nxx/type_trait/copy_cv.hpp>
#include <nxx/type_trait/is_enum.hpp>
#include <nxx/type_trait/is_integral.hpp>
#include <nxx/type_trait/remove_cv.hpp>

namespace nxx::impl {

template<typename T, bool = is_integral<T>::value || is_enum<T>::value>
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

template<typename T>
struct make_unsigned
{
    using type = typename copy_cv<T>::template type<typename make_unsigned_impl<typename remove_cv<T>::type>::type>;
};

} // namespace nxx::impl

namespace nxx {

template<class T>
using make_unsigned = typename impl::make_unsigned<T>::type;

} // namespace nxx
