#pragma once

#include <nxx/def.hpp>

namespace nxx {

constexpr size_t round_to_alignment(size_t size, size_t align)
{
    return size + ((size % align) == 0 ? 0 : align - (size % align));
}

} // namespace nxx
