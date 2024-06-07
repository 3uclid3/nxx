#pragma once

#include <nxx/type_trait/conditional.hpp>

namespace nxx::details {

template<typename T>
constexpr bool is_array_param_by_value = sizeof(T) <= 2 * sizeof(void*);

template<typename T>
using array_param_type = conditional<is_array_param_by_value<T>, T, const T&>;

} // namespace nxx::details
