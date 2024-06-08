#pragma once

#include <nxx/type_trait/is_same.hpp>
#include <nxx/type_trait/remove_cv.hpp>

namespace nxx::impl {

template<typename T>
struct is_void : is_same<remove_cv<T>, void>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_void = impl::is_void<T>::value;

} // namespace nxx
