#pragma once

#include <nxx/def.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

class null_allocator
{
public:
    [[nodiscard]] constexpr bool owns(const_memory_block block) const;
    [[nodiscard]] constexpr memory_block allocate(size_t size);
    constexpr void deallocate(memory_block block);
};

constexpr bool null_allocator::owns(const_memory_block block) const
{
    return block.is_null();
}

constexpr memory_block null_allocator::allocate(size_t size)
{
    NXX_UNUSED(size);
    return nullblk;
}

constexpr void null_allocator::deallocate(memory_block block)
{
    NXX_UNUSED(block);
    NXX_ASSERT(block.is_null());
}

} // namespace nxx
