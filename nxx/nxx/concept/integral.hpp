#pragma once

#include <nxx/type_trait/is_integral.hpp>

namespace nxx {

template<typename T>
concept integral = is_integral<T>;

} // namespace nxx
