#pragma once

#include <nxx/def.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

[[nodiscard]] memory_block allocate(size_t size);
bool expand_allocate(memory_block& block, size_t delta);
bool reallocate(memory_block& block, size_t new_size);
void deallocate(memory_block& block);

} // namespace nxx
