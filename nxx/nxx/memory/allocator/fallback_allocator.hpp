#pragma once

#include <nxx/memory/allocator/allocator_trait.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
class fallback_allocator : private PrimaryAllocatorT, private FallbackAllocatorT
{
public:
    using primary = PrimaryAllocatorT;
    using fallback = FallbackAllocatorT;

    static constexpr bool supports_truncated_deallocation = primary::supports_truncated_deallocation || fallback::supports_truncated_deallocation;
    static constexpr unsigned alignment = primary::alignment > fallback::alignment ? primary::alignment : fallback::alignment;

public:
    [[nodiscard]] constexpr memory_block allocate(size_t size);

    template<typename U = PrimaryAllocatorT, typename V = FallbackAllocatorT>
    requires(allocator_trait::has_owns<U> && allocator_trait::has_owns<V>)
    [[nodiscard]] constexpr bool owns(const memory_block& block) const;

    template<typename U = PrimaryAllocatorT, typename V = FallbackAllocatorT>
    requires(allocator_trait::has_expand<U> || allocator_trait::has_expand<V>)
    constexpr bool expand(memory_block& block, size_t delta);
    constexpr bool reallocate(memory_block& block, size_t new_size);
    constexpr void deallocate(memory_block& block);

    template<typename U = PrimaryAllocatorT, typename V = FallbackAllocatorT>
    requires(allocator_trait::has_deallocate_all<U> && allocator_trait::has_deallocate_all<V>)
    constexpr void deallocate_all();
};

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
constexpr memory_block fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::allocate(size_t size)
{
    if (size == 0)
    {
        return nullblk;
    }

    if (memory_block block = primary::allocate(size))
    {
        return block;
    }

    return fallback::allocate(size);
}

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
template<typename U, typename V>
requires(allocator_trait::has_owns<U> && allocator_trait::has_owns<V>)
constexpr bool fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::owns(const memory_block& block) const
{
    return primary::owns(block) || fallback::owns(block);
}

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
template<typename U, typename V>
requires(allocator_trait::has_expand<U> || allocator_trait::has_expand<V>)
constexpr bool fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::expand(memory_block& block, size_t delta)
{
    if constexpr (allocator_trait::has_expand<primary>)
    {
        if (primary::owns(block))
        {
            return primary::expand(block, delta);
        }
    }

    if constexpr (allocator_trait::has_expand<fallback>)
    {
        return fallback::expand(block, delta);
    }

    return false;
}

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
constexpr bool fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::reallocate(memory_block& block, size_t new_size)
{
    if (primary::owns(block))
    {
        if (primary::reallocate(block, new_size))
        {
            return true;
        }

        if (memory_block new_block = fallback::allocate(new_size))
        {
            memcpy(new_block.ptr, block.ptr, block.size);
            primary::deallocate(block);
            block = new_block;

            return true;
        }

        return false;
    }

    return fallback::reallocate(block, new_size);
}

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
constexpr void fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::deallocate(memory_block& block)
{
    if (!block)
    {
        return;
    }

    if (primary::owns(block))
    {
        primary::deallocate(block);
    }
    else
    {
        fallback::deallocate(block);
    }
}

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
template<typename U, typename V>
requires(allocator_trait::has_deallocate_all<U> && allocator_trait::has_deallocate_all<V>)
constexpr void fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::deallocate_all()
{
    primary::deallocate_all();
    fallback::deallocate_all();
}

} // namespace nxx