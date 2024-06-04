#pragma once

#ifndef NXX_NO_DECLARE_NEW_OPERATOR

#include <nxx/def.hpp>

[[nodiscard]] void* operator new(nxx::size_t size);
[[nodiscard]] void* operator new[](nxx::size_t size);
[[nodiscard]] void* operator new(nxx::size_t size, void* ptr);
[[nodiscard]] void* operator new[](nxx::size_t size, void* ptr);

void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;
void operator delete(void* ptr, nxx::size_t size) noexcept;
void operator delete[](void* ptr, nxx::size_t size) noexcept;
void operator delete(void* ptr, void* place) noexcept;
void operator delete[](void* ptr, void* place) noexcept;

[[nodiscard]] inline void* operator new(nxx::size_t size, void* ptr)
{
    NXX_UNUSED(size);
    return ptr;
}

[[nodiscard]] inline void* operator new[](nxx::size_t size, void* ptr)
{
    NXX_UNUSED(size);
    return ptr;
}

inline void operator delete(void* ptr, void* place) noexcept
{
    NXX_UNUSED(ptr);
    NXX_UNUSED(place);
}

inline void operator delete[](void* ptr, void* place) noexcept
{
    NXX_UNUSED(ptr);
    NXX_UNUSED(place);
}

#endif
