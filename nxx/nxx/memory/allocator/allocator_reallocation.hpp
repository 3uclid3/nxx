#pragma once

#include <nxx/def.hpp>
#include <nxx/memory/memory_block.hpp>
#include <nxx/memory/utility.hpp>

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

template<typename OriginalAllocatorT, typename NewAllocatorT>
constexpr bool reallocate_with_new_allocator(OriginalAllocatorT& original_allocator, NewAllocatorT& new_allocator, memory_block& block, size_t new_size)
{
    if (memory_block new_block = new_allocator.allocate(new_size))
    {
        memcpy(new_block.ptr, block.ptr, block.size);
        original_allocator.deallocate(block);
        block = new_block;

        return true;
    }

    return false;
}

} // namespace nxx
