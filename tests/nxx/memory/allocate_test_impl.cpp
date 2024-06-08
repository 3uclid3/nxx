#include <nxx/memory/allocate.hpp>

#include <malloc.h>
#include <new>

#include <nxx/memory/allocator/affix/memory_corruption_detector.hpp>
#include <nxx/memory/allocator/affix_allocator.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

namespace details {

struct malloc_allocator
{
    static constexpr size_t alignment = 8;

    [[nodiscard]] constexpr memory_block allocate(size_t size)
    {
        return memory_block(malloc(size), size);
    }

    [[nodiscard]] constexpr bool owns(const memory_block& block) const
    {
        return block;
    }

    constexpr bool reallocate(memory_block& block, size_t new_size)
    {
        void* new_ptr = realloc(block.ptr, new_size);

        if (new_ptr == nullptr)
        {
            return false;
        }

        block.ptr = new_ptr;
        block.size = new_size;

        return true;
    }

    constexpr void deallocate(memory_block& block)
    {
        free(block.ptr);

        block = nullblk;
    }
};

using test_memory_corruption_detector = memory_corruption_detector<u32_t, 0xDEADBEEF, 32>;
using test_allocator = affix_allocator<malloc_allocator, test_memory_corruption_detector, test_memory_corruption_detector>;

test_allocator allocator;

} // namespace details

memory_block allocate(size_t size)
{
    return details::allocator.allocate(size);
}

void deallocate(memory_block& block)
{
    details::allocator.deallocate(block);
}

} // namespace nxx