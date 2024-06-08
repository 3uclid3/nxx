#pragma once

#include <nxx/type_trait/copy_cv.hpp>
#include <nxx/type_trait/is_enum.hpp>
#include <nxx/type_trait/is_integral.hpp>
#include <nxx/type_trait/remove_cv.hpp>

namespace nxx::impl {

template<typename T, bool = is_integral<T>::value || is_enum<T>::value>
struct make_signed_impl
{};

// clang-format off
template <> struct make_signed_impl<bool, true> {};
template <> struct make_signed_impl<s8_t, true> { using type = s8_t; };
template <> struct make_signed_impl<u8_t, true> { using type = s8_t; };
template <> struct make_signed_impl<s16_t, true> { using type = s16_t; };
template <> struct make_signed_impl<u16_t, true> { using type = s16_t; };
template <> struct make_signed_impl<s32_t, true> { using type = s32_t; };
template <> struct make_signed_impl<u32_t, true> { using type = s32_t; };
template <> struct make_signed_impl<s64_t, true> { using type = s64_t; };
template <> struct make_signed_impl<u64_t, true> { using type = s64_t; };
// clang-format on

template<typename T>
struct make_signed
{
    using type = typename copy_cv<T>::template type<typename make_signed_impl<remove_cv<T>::type>::type>;
};

} // namespace nxx::impl

namespace nxx {

template<class T>
using make_signed = typename impl::make_signed<T>::type;

} // namespace nxx
