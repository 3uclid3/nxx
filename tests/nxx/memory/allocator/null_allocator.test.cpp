#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <nxx/memory/allocator/null_allocator.hpp>

namespace nxx {

TEST_CASE("null_allocator owns nullblk", "[memory]")
{
    null_allocator allocator;
    memory_block block(&allocator, sizeof(null_allocator));

    CHECK(allocator.owns(nullblk));
    CHECK_FALSE(allocator.owns(block));
}

TEST_CASE("null_allocator allocate nullblk", "[memory]")
{
    size_t size = GENERATE(4, 8, 12, 16, 32);

    null_allocator allocator;
    CHECK(allocator.allocate(size) == nullblk);
}

TEST_CASE("null_allocator cannot expand", "[memory]")
{
    memory_block block = nullblk;

    null_allocator allocator;
    CHECK_FALSE(allocator.expand(block, 1));
    CHECK(block == nullblk);
}

TEST_CASE("null_allocator cannot reallocate", "[memory]")
{
    memory_block block = nullblk;

    null_allocator allocator;
    CHECK_FALSE(allocator.reallocate(block, 1));
    CHECK(block == nullblk);
}

TEST_CASE("null_allocator cannot deallocate", "[memory]")
{
    memory_block block = nullblk;

    null_allocator allocator;
    allocator.deallocate(block);
    CHECK(block == nullblk);
}

} // namespace nxx
