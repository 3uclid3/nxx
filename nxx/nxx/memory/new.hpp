#pragma once

#include <nxx/def.hpp>

[[nodiscard]] extern void* operator new(nxx::size_t size);
[[nodiscard]] extern void* operator new[](nxx::size_t size);
[[nodiscard]] extern void* operator new(nxx::size_t size, void* ptr) noexcept;
[[nodiscard]] extern void* operator new[](nxx::size_t size, void* ptr) noexcept;

extern void operator delete(void* ptr) noexcept;
extern void operator delete[](void* ptr) noexcept;
extern void operator delete(void* ptr, nxx::size_t size) noexcept;
extern void operator delete[](void* ptr, nxx::size_t size) noexcept;
extern void operator delete(void* ptr, void* place) noexcept;
extern void operator delete[](void* ptr, void* place) noexcept;
