#pragma once

namespace nxx {

template<typename T>
using add_lvalue_reference = __add_lvalue_reference(T);

} // namespace nxx
