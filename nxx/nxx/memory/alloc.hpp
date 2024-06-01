#pragma once

#include <nxx/def.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

memory_block allocate(size_t size);
void deallocate(memory_block block);

} // namespace nxx
