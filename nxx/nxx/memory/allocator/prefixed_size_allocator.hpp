#pragma once

#include <nxx/def.hpp>
#include <nxx/memory/allocator/affix_allocator.hpp>
#include <nxx/memory/allocator/allocator_reallocation.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

template<typename AllocatorT>
class prefixed_size_allocator : private affix_allocator<AllocatorT, size_t>
{
    using super = affix_allocator<AllocatorT, size_t>;

public:
    static constexpr size_t alignment = super::alignment;

public:
    [[nodiscard]] constexpr size_t get_alignment() const;

    [[nodiscard]] constexpr memory_block allocate(size_t size);

    template<typename U = AllocatorT>
    requires(allocator_traits::has_owns<U>)
    [[nodiscard]] constexpr bool owns(const memory_block& block) const;

    template<typename U = AllocatorT>
    requires(allocator_traits::has_expand<U>)
    constexpr bool expand(memory_block& block, size_t delta);
    constexpr bool reallocate(memory_block& block, size_t new_size);
    constexpr void deallocate(memory_block& block);

    constexpr size_t get_prefixed_size(const memory_block& block) const;

private:
    constexpr void set_prefixed_size(const memory_block& block, size_t size);
};

template<typename AllocatorT>
constexpr size_t prefixed_size_allocator<AllocatorT>::get_alignment() const
{
    return alignment;
}

template<typename AllocatorT>
constexpr memory_block prefixed_size_allocator<AllocatorT>::allocate(size_t size)
{
    if (memory_block block = super::allocate(size))
    {
        set_prefixed_size(block, size);
        return block;
    }
    return nullblk;
}

template<typename AllocatorT>
template<typename U>
requires(allocator_traits::has_owns<U>)
constexpr bool prefixed_size_allocator<AllocatorT>::owns(const memory_block& block) const
{
    return block && super::owns(memory_block(block.ptr, get_prefixed_size(block)));
}

template<typename AllocatorT>
template<typename U>
requires(allocator_traits::has_expand<U>)
constexpr bool prefixed_size_allocator<AllocatorT>::expand(memory_block& block, size_t delta)
{
    if (delta == 0)
    {
        return true;
    }

    if (!block)
    {
        block = allocate(delta);
        return block;
    }

    memory_block sized_block(block.ptr, get_prefixed_size(block));

    if (!super::expand(sized_block, delta))
    {
        return false;
    }

    set_prefixed_size(sized_block, sized_block.size);

    block.ptr = sized_block.ptr;
    block.size += delta;
    return true;
}

template<typename AllocatorT>
constexpr bool prefixed_size_allocator<AllocatorT>::reallocate(memory_block& block, size_t new_size)
{
    if (auto [success, reallocated] = try_default_reallocate(*this, block, new_size); success)
    {
        return reallocated;
    }

    memory_block sized_block(block.ptr, get_prefixed_size(block));

    if (!super::reallocate(sized_block, new_size))
    {
        return false;
    }

    set_prefixed_size(sized_block, sized_block.size);

    block.ptr = sized_block.ptr;
    block.size = new_size;
    return true;
}

template<typename AllocatorT>
constexpr void prefixed_size_allocator<AllocatorT>::deallocate(memory_block& block)
{
    if (block)
    {
        memory_block sized_block(block.ptr, get_prefixed_size(block));
        super::deallocate(sized_block);
        block = nullblk;
    }
}

template<typename AllocatorT>
constexpr size_t prefixed_size_allocator<AllocatorT>::get_prefixed_size(const memory_block& block) const
{
    const size_t* ptr = super::get_prefix(block);
    NXX_ASSERT(ptr != nullptr);
    return *ptr;
}

template<typename AllocatorT>
constexpr void prefixed_size_allocator<AllocatorT>::set_prefixed_size(const memory_block& block, size_t size)
{
    size_t* ptr = super::get_prefix(block);
    NXX_ASSERT(ptr != nullptr);
    *ptr = size;
}

} // namespace nxx
