#include <nxx/memory/allocate.hpp>

#include <malloc.h>

#include <nxx/memory/memory_block.hpp>

namespace nxx {

memory_block allocate(size_t size)
{
    return memory_block(malloc(size), size);
}

void deallocate(memory_block& block)
{
    free(block.ptr);

    block = nullblk;
}

} // namespace nxx