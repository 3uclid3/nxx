#include <catch2/catch_test_macros.hpp>

#include <nxx/memory/allocator/null-allocator.hpp>

namespace nxx {

TEST_CASE("null_allocator owns nullblk", "[memory]")
{
    null_allocator allocator;
    CHECK(allocator.owns(nullblk));

    memory_block allocator_block{.pointer = &allocator, .size = sizeof(null_allocator)};
    CHECK_FALSE(allocator.owns(allocator_block));
}

TEST_CASE("null_allocator allocate returns nullblk", "[memory]")
{
    null_allocator allocator;
    CHECK(allocator.allocate(12) == nullblk);
    CHECK(allocator.allocate(42) == nullblk);
}

TEST_CASE("null_allocator deallocate accept nullblk", "[memory]")
{
    null_allocator allocator;
    allocator.deallocate(nullblk); // asserts otherwise
    SUCCEED();
}

} // namespace nxx
