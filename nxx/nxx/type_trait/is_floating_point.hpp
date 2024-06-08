#pragma once

#include <nxx/def.hpp>
#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename T>
struct is_floating_point : false_type
{};

template<>
struct is_floating_point<f32_t> : true_type
{};

template<>
struct is_floating_point<f64_t> : true_type
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_floating_point = impl::is_floating_point<T>::value;

} // namespace nxx
