#pragma once

#include <nxx/container/details/array_object.hpp>
#include <nxx/container/details/array_trivial.hpp>
#include <nxx/type_trait/conditional.hpp>
#include <nxx/type_trait/is_trivially_copy_constructible.hpp>
#include <nxx/type_trait/is_trivially_destructible.hpp>
#include <nxx/type_trait/is_trivially_move_constructible.hpp>

namespace nxx::details {

// Does T requires a array_trivial class
template<typename T>
inline constexpr bool is_trivial_array = is_trivially_copy_constructible<T> && // not standard
                                         is_trivially_move_constructible<T> && // but POD can't know
                                         is_trivially_destructible<T>;

template<typename T, typename SizeT>
using array_base_type = conditional<is_trivial_array<T>, array_trivial<T, SizeT>, array_object<T, SizeT>>;

} // namespace nxx::details