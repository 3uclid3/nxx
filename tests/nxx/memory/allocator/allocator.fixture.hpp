#pragma once

#include <nxx/memory/memory_block.hpp>

namespace nxx {

template<typename AllocatorT>
struct allocator_fixture
{
    using allocator_type = AllocatorT;

    void deallocate_and_check_is_nullblk(memory_block& block)
    {
        allocator.deallocate(block);
        CHECK(block == nullblk);
    }

    AllocatorT allocator;
};

} // namespace nxx
