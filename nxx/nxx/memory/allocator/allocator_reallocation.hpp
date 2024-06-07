#pragma once

#include <nxx/def.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

template<typename AllocatorT>
constexpr bool try_default_reallocate(AllocatorT& allocator, memory_block& block, size_t new_size)
{
    if (block.size == new_size)
    {
        return true;
    }

    if (new_size == 0)
    {
        allocator.deallocate(block);
        return true;
    }

    if (!block)
    {
        block = allocator.allocate(new_size);
        return true;
    }

    return false;
}

} // namespace nxx
