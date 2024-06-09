#pragma once

#include <nxx/def.hpp>
#include <nxx/memory/allocator/allocator_reallocation.hpp>
#include <nxx/memory/allocator/allocator_traits.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

template<typename SmallAllocatorT, typename LargeAllocatorT, size_t ThresholdT>
class segregator_allocator : private SmallAllocatorT, private LargeAllocatorT
{
public:
    using small = SmallAllocatorT;
    using large = LargeAllocatorT;

    static constexpr size_t alignment = small::alignment > large::alignment ? small::alignment : large::alignment;
    static constexpr size_t threshold = ThresholdT;

public:
    [[nodiscard]] constexpr memory_block allocate(size_t size);

    template<typename U = SmallAllocatorT, typename V = LargeAllocatorT>
    requires(allocator_traits::has_owns<U> && allocator_traits::has_owns<V>)
    [[nodiscard]] constexpr bool owns(const memory_block& block) const;

    template<typename U = SmallAllocatorT, typename V = LargeAllocatorT>
    requires(allocator_traits::has_expand<U> || allocator_traits::has_expand<V>)
    constexpr bool expand(memory_block& block, size_t delta);
    constexpr bool reallocate(memory_block& block, size_t new_size);
    constexpr void deallocate(memory_block& block);

    template<typename U = SmallAllocatorT, typename V = LargeAllocatorT>
    requires(allocator_traits::has_deallocate_all<U> && allocator_traits::has_deallocate_all<V>)
    constexpr void deallocate_all();

private:
    constexpr bool is_small(size_t size) const;
    
    static_assert(ThresholdT > 0, "Threshold must be greater than 0");
    static_assert(round_to_alignment(ThresholdT, alignment) == ThresholdT, "Threshold must be a multiple of the alignment");
};

template<typename SmallAllocatorT, typename LargeAllocatorT, size_t ThresholdT>
constexpr memory_block segregator_allocator<SmallAllocatorT, LargeAllocatorT, ThresholdT>::allocate(size_t size)
{
    if (is_small(size))
    {
        return small::allocate(size);
    }

    return large::allocate(size);
}

template<typename SmallAllocatorT, typename LargeAllocatorT, size_t ThresholdT>
template<typename U, typename V>
requires(allocator_traits::has_owns<U> && allocator_traits::has_owns<V>)
constexpr bool segregator_allocator<SmallAllocatorT, LargeAllocatorT, ThresholdT>::owns(const memory_block& block) const
{
    if (is_small(block.size))
    {
        return small::owns(block);
    }

    return large::owns(block);
}

template<typename SmallAllocatorT, typename LargeAllocatorT, size_t ThresholdT>
template<typename U, typename V>
requires(allocator_traits::has_expand<U> || allocator_traits::has_expand<V>)
constexpr bool segregator_allocator<SmallAllocatorT, LargeAllocatorT, ThresholdT>::expand(memory_block& block, size_t delta)
{
    if (is_small(block.size))
    {
        if constexpr (allocator_traits::has_expand<SmallAllocatorT>)
        {
            return small::expand(block, delta);
        }
    }
    else if constexpr (allocator_traits::has_expand<LargeAllocatorT>)
    {
        return large::expand(block, delta);
    }

    return false;
}

template<typename SmallAllocatorT, typename LargeAllocatorT, size_t ThresholdT>
constexpr bool segregator_allocator<SmallAllocatorT, LargeAllocatorT, ThresholdT>::reallocate(memory_block& block, size_t new_size)
{
    if (try_default_reallocate(*this, block, new_size))
    {
        return block;
    }

    // from small block?
    if (is_small(block.size))
    {
        if (is_small(new_size))
        {
            return small::reallocate(block, new_size);
        }

        return reallocate_with_new_allocator<small, large>(*this, *this, block, new_size);
    }

    // from large block to small block?
    if (is_small(new_size))
    {
        return reallocate_with_new_allocator<large, small>(*this, *this, block, new_size);
    }
    
    return large::reallocate(block, new_size);
}

template<typename SmallAllocatorT, typename LargeAllocatorT, size_t ThresholdT>
constexpr void segregator_allocator<SmallAllocatorT, LargeAllocatorT, ThresholdT>::deallocate(memory_block& block)
{
    if (is_small(block.size))
    {
        small::deallocate(block);
    }
    else
    {
        large::deallocate(block);
    }
}

template<typename SmallAllocatorT, typename LargeAllocatorT, size_t ThresholdT>
template<typename U, typename V>
requires(allocator_traits::has_deallocate_all<U> && allocator_traits::has_deallocate_all<V>)
constexpr void segregator_allocator<SmallAllocatorT, LargeAllocatorT, ThresholdT>::deallocate_all()
{
    small::deallocate_all();
    large::deallocate_all();
}

template<typename SmallAllocatorT, typename LargeAllocatorT, size_t ThresholdT>
constexpr bool segregator_allocator<SmallAllocatorT, LargeAllocatorT, ThresholdT>::is_small(size_t size) const
{
    return size <= threshold;
}

} // namespace nxx
