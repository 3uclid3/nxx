#pragma once

#include <nxx/def.hpp>
#include <nxx/type_trait/conditional.hpp>

namespace nxx::details {

template<class T>
using array_size_type = conditional<sizeof(T) < 4 && sizeof(void*) >= 8, u64_t, u32_t>;

} // namespace nxx::details