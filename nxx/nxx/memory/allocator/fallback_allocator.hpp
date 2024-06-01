#pragma once

#include <nxx/memory/memory_block.hpp>

namespace nxx {

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
class fallback_allocator : private PrimaryAllocatorT, private FallbackAllocatorT
{
public:
    constexpr bool owns(const_memory_block block) const;
    constexpr memory_block allocate(size_t size);
    constexpr void deallocate(memory_block block);
};

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
constexpr bool fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::owns(const_memory_block block) const
{
    return PrimaryAllocatorT::owns(block) || FallbackAllocatorT::owns(block);
}

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
constexpr memory_block fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::allocate(size_t size)
{
    memory_block block = PrimaryAllocatorT::allocate(size);

    if (!block.is_null())
    {
        return block;
    }

    return FallbackAllocatorT::allocate(size);
}

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
constexpr void fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::deallocate(memory_block block)
{
    if (PrimaryAllocatorT::owns(block))
    {
        PrimaryAllocatorT::deallocate(block);
    }
    else if (FallbackAllocatorT::owns(block))
    {
        FallbackAllocatorT::deallocate(block);
    }
}

} // namespace nxx
