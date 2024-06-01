#pragma once

#include <nxx/type_trait/integral_constant.hpp>
#include <nxx/def.hpp>

namespace nxx::details {

template<typename T>
struct is_floating_point_impl : false_type
{};

template<>
struct is_floating_point_impl<f32_t> : true_type
{};

template<>
struct is_floating_point_impl<f64_t> : true_type
{};

} // namespace nxx::details
