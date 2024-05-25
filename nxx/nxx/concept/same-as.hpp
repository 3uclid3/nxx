#pragma once

#include <nxx/type-trait/is-same.hpp>

namespace nxx {
namespace details {

template<class T0, class T1>
concept same_as = is_same<T0, T1>;

} // namespace details

template<typename T0, typename T1>
concept same_as = (details::same_as<T0, T1> && details::same_as<T1, T0>);

} // namespace nxx
