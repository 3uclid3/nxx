#include <nxx/memory/new.hpp>

#include <malloc.h>

#include <nxx/def.hpp>
#include <nxx/memory/memory-block.hpp>

[[nodiscard]] void* operator new(nxx::size_t size)
{
    return malloc(size);
}

[[nodiscard]] void* operator new[](nxx::size_t size)
{
    return malloc(size);
}

void operator delete(void* ptr) noexcept
{
    free(ptr);
}

void operator delete[](void* ptr) noexcept
{
    free(ptr);
}

void operator delete(void* ptr, nxx::size_t size) noexcept
{
    NXX_UNUSED(size);
    free(ptr);
}

void operator delete[](void* ptr, nxx::size_t size) noexcept
{
    NXX_UNUSED(size);
    free(ptr);
}