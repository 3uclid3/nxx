#include <nxx/memory/memory_block.hpp>

#include <catch2/catch_test_macros.hpp>

namespace nxx {

TEST_CASE("memory_block", "[memory]")
{
    memory_block block;

    CHECK(block == nullblk);
    CHECK(!block);

    block.ptr = &block;
    block.size = sizeof(block);

    CHECK(block != nullblk);
    CHECK(block);
}

} // namespace nxx
