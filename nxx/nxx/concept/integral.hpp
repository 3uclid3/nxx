#pragma once

#include <nxx/type-trait/is-integral.hpp>

namespace nxx {

template<typename T>
concept integral = is_integral<T>;

} // namespace nxx
