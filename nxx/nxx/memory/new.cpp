#include <nxx/memory/new.hpp>

#include <nxx/memory/allocate.hpp>

[[nodiscard]] void* operator new(nxx::size_t size) noexcept
{
    return nxx::allocate(size).ptr
}

[[nodiscard]] void* operator new[](nxx::size_t size) noexcept
{
    return nxx::allocate(size).ptr;
}

[[nodiscard]] void* operator new(nxx::size_t size, void* ptr)
{
    NXX_UNUSED(size);
    return ptr;
}

[[nodiscard]] void* operator new[](nxx::size_t size, void* ptr)
{
    NXX_UNUSED(size);
    return ptr;
}

void operator delete(void* ptr) noexcept
{
    nxx::memory_block block{ptr, 0};
    nxx::deallocate(block);
}

void operator delete[](void* ptr) noexcept
{
    nxx::memory_block block{ptr, 0};
    nxx::deallocate(block);
}

void operator delete(void* ptr, nxx::size_t size) noexcept
{
    nxx::memory_block block{ptr, size};
    nxx::deallocate(block);
}

void operator delete[](void* ptr, nxx::size_t size) noexcept
{
    nxx::memory_block block{ptr, size};
    nxx::deallocate(block);
}

void operator delete(void* ptr, void* place) noexcept
{
    NXX_UNUSED(ptr);
    NXX_UNUSED(place);
}

void operator delete[](void* ptr, void* place) noexcept
{
    NXX_UNUSED(ptr);
    NXX_UNUSED(place);
}
