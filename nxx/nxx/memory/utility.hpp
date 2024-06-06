#pragma once

#include <nxx/def.hpp>

namespace nxx {

int memcmp(const void* lhs, const void* rhs, size_t size);
void* memcpy(void* dest, const void* src, size_t size);
void* memset(void* ptr, int val, size_t size);
void* memmove(void* dest, const void* src, size_t size);

} // namespace nxx
