#pragma once

#include <nxx/def.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

class null_allocator
{
public:
    static constexpr size_t alignment = 64 * 1024;

public:
    constexpr size_t get_alignment() const;

    [[nodiscard]] constexpr memory_block allocate(size_t size);
    [[nodiscard]] constexpr bool owns(const memory_block& block) const;
    constexpr bool expand(memory_block& block, size_t delta);
    constexpr bool reallocate(memory_block& block, size_t new_size);
    constexpr void deallocate(memory_block& block);
    constexpr void deallocate_all();
};

constexpr size_t null_allocator::get_alignment() const
{
    return alignment;
}

constexpr memory_block null_allocator::allocate(size_t size)
{
    NXX_UNUSED(size);
    return nullblk;
}

constexpr bool null_allocator::owns(const memory_block& block) const
{
    return !block;
}

constexpr bool null_allocator::expand(memory_block& block, size_t delta)
{
    NXX_UNUSED(block);
    NXX_UNUSED(delta);
    NXX_ASSERT(!block);
    return false;
}

constexpr bool null_allocator::reallocate(memory_block& block, size_t new_size)
{
    NXX_UNUSED(block);
    NXX_UNUSED(new_size);
    NXX_ASSERT(!block);
    return false;
}

constexpr void null_allocator::deallocate(memory_block& block)
{
    NXX_UNUSED(block);
    NXX_ASSERT(!block);
}

constexpr void null_allocator::deallocate_all()
{
}

} // namespace nxx
