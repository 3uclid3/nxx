#include <catch2/catch_test_macros.hpp>

#include <nxx/memory/allocator/stack-allocator.hpp>

namespace nxx {

using stack_allocator64 = stack_allocator<64>;

TEST_CASE("stack_allocator::allocate", "[memory]")
{
    stack_allocator64 allocator64;

    SECTION("returns block if size < stack size")
    {
        memory_block block = allocator64.allocate(stack_allocator64::max_size - 2);

        CHECK(block != nullblk);
    }

    SECTION("returns block if size == stack size")
    {
        memory_block block = allocator64.allocate(stack_allocator64::max_size);

        CHECK(block != nullblk);
    }

    SECTION("returns nullblk if size is 0")
    {
        memory_block block = allocator64.allocate(0);

        CHECK(block == nullblk);
    }

    SECTION("returns nullblk if size > stack size")
    {
        memory_block block = allocator64.allocate(stack_allocator64::max_size + 1);

        CHECK(block == nullblk);
    }

    SECTION("returns nullblk if size > remaining stack size")
    {
        memory_block block = allocator64.allocate(1);

        REQUIRE(block != nullblk);

        block = allocator64.allocate(stack_allocator64::max_size);

        CHECK(block == nullblk);
    }

    SECTION("returns nullblk if size > remaining stack size")
    {
        memory_block block = allocator64.allocate(stack_allocator64::max_size - 1);

        REQUIRE(block != nullblk);

        block = allocator64.allocate(2);

        CHECK(block == nullblk);
    }

    SECTION("returns nullblk if stack empty")
    {
        memory_block block = allocator64.allocate(stack_allocator64::max_size);

        REQUIRE(block != nullblk);

        block = allocator64.allocate(1);

        CHECK(block == nullblk);
    }
}

TEST_CASE("stack_allocator::deallocate", "[memory]")
{
    // fill the allocator and use that information to verify the deallocation has succeeded
    static constexpr size_t alloc_size = stack_allocator64::max_size / 2;

    stack_allocator64 allocator;

    memory_block first_block = allocator.allocate(alloc_size);
    memory_block last_block = allocator.allocate(alloc_size);

    REQUIRE(first_block != nullblk);
    REQUIRE(last_block != nullblk);

    SECTION("if last allocated block")
    {
        allocator.deallocate(last_block);

        memory_block newBlock = allocator.allocate(alloc_size);

        CHECK(newBlock == last_block);
    }

    SECTION("nothing not last allocated block")
    {
        allocator.deallocate(first_block);

        memory_block newBlock = allocator.allocate(alloc_size);

        // allocator was full
        CHECK(newBlock == nullblk);
    }
}

} // namespace nxx