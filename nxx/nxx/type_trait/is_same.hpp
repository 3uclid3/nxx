#pragma once

#include <nxx/type_trait/details/is_same_impl.hpp>

namespace nxx {

template<typename T0, typename T1>
inline constexpr bool is_same = details::is_same_impl<T0, T1>::value;

} // namespace nxx
