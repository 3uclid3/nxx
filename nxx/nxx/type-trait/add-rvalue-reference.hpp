#pragma once

namespace nxx {

template<typename T>
using add_rvalue_reference = __add_rvalue_reference(T);

} // namespace nxx
