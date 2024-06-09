#pragma once

#include <nxx/memory/allocator/allocator_reallocation.hpp>
#include <nxx/memory/allocator/allocator_traits.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
class fallback_allocator : private PrimaryAllocatorT, private FallbackAllocatorT
{
public:
    using primary = PrimaryAllocatorT;
    using fallback = FallbackAllocatorT;

    static constexpr size_t alignment = primary::alignment > fallback::alignment ? primary::alignment : fallback::alignment;

public:
    [[nodiscard]] constexpr size_t get_alignment() const;

    [[nodiscard]] constexpr memory_block allocate(size_t size);

    template<typename U = PrimaryAllocatorT, typename V = FallbackAllocatorT>
    requires(allocator_traits::has_owns<U> && allocator_traits::has_owns<V>)
    [[nodiscard]] constexpr bool owns(const memory_block& block) const;

    template<typename U = PrimaryAllocatorT, typename V = FallbackAllocatorT>
    requires(allocator_traits::has_expand<U> || allocator_traits::has_expand<V>)
    constexpr bool expand(memory_block& block, size_t delta);
    constexpr bool reallocate(memory_block& block, size_t new_size);
    constexpr void deallocate(memory_block& block);

    template<typename U = PrimaryAllocatorT, typename V = FallbackAllocatorT>
    requires(allocator_traits::has_deallocate_all<U> && allocator_traits::has_deallocate_all<V>)
    constexpr void deallocate_all();
};

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
constexpr size_t fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::get_alignment() const
{
    return alignment;
}

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
requires(allocator_traits::has_owns<U> && allocator_traits::has_owns<V>)
constexpr bool fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::owns(const memory_block& block) const
{
    return primary::owns(block) || fallback::owns(block);
}

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
template<typename U, typename V>
requires(allocator_traits::has_expand<U> || allocator_traits::has_expand<V>)
constexpr bool fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::expand(memory_block& block, size_t delta)
{
    if constexpr (allocator_traits::has_expand<primary>)
    {
        if (primary::owns(block))
        {
            return primary::expand(block, delta);
        }
    }

    if constexpr (allocator_traits::has_expand<fallback>)
    {
        return fallback::expand(block, delta);
    }

    return false;
}

template<typename PrimaryAllocatorT, typename FallbackAllocatorT>
constexpr bool fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::reallocate(memory_block& block, size_t new_size)
{
    const bool is_primary_owner = primary::owns(block);

    if (is_primary_owner)
    {
        if (auto [success, reallocated] = try_default_reallocate<primary>(*this, block, new_size); success)
        {
            return reallocated;
        }
    }
    else if (auto [success, reallocated] = try_default_reallocate<fallback>(*this, block, new_size); success)
    {
        return reallocated;
    }

    if (is_primary_owner)
    {
        if (primary::reallocate(block, new_size))
        {
            return true;
        }

        return reallocate_with_new_allocator<primary, fallback>(*this, *this, block, new_size);
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
requires(allocator_traits::has_deallocate_all<U> && allocator_traits::has_deallocate_all<V>)
constexpr void fallback_allocator<PrimaryAllocatorT, FallbackAllocatorT>::deallocate_all()
{
    primary::deallocate_all();
    fallback::deallocate_all();
}

} // namespace nxx
