#include <nxx/memory/new.hpp>

#ifndef NXX_NO_DECLARE_NEW_OPERATOR

#include <nxx/def.hpp>
#include <nxx/memory/allocate.hpp>

[[nodiscard]] void* operator new(nxx::size_t size)
{
    return nxx::allocate(size).pointer;
}

[[nodiscard]] void* operator new[](nxx::size_t size)
{
    return nxx::allocate(size).pointer;
}

void operator delete(void* ptr) noexcept
{
    NXX_ASSERT(false, "delete called without providing size");
    nxx::memory_block block{.pointer = ptr, .size = 0};
    nxx::deallocate(block);
}

void operator delete[](void* ptr) noexcept
{
    NXX_ASSERT(false, "delete called without providing size");
    nxx::memory_block block{.pointer = ptr, .size = 0};
    nxx::deallocate(block);
}

void operator delete(void* ptr, nxx::size_t size) noexcept
{
    nxx::memory_block block{.pointer = ptr, .size = size};
    nxx::deallocate(block);
}

void operator delete[](void* ptr, nxx::size_t size) noexcept
{
    nxx::memory_block block{.pointer = ptr, .size = size};
    nxx::deallocate(block);
}

#endif
