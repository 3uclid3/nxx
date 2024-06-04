#include <nxx/memory/alloc.hpp>

#include <malloc.h>

#include <nxx/memory/memory_block.hpp>

namespace nxx {

memory_block allocate(size_t size)
{
    return {.pointer = malloc(size), .size = size};
}

void deallocate(memory_block block)
{
    free(block.pointer);
}

} // namespace nxx