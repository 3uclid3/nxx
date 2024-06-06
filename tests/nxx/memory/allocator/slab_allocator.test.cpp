#include <catch2/catch_test_macros.hpp>

#include <vector>

#include <nxx/memory/allocator/slab_allocator.hpp>
#include <nxx/memory/allocator/stack_allocator.hpp>

namespace nxx {

TEST_CASE("slab_allocator allocate and deallocate objects with sizes matching slab sizes")
{
    slab_allocator<stack_allocator<1024>, 4, 32, 64, 128> allocator;

    memory_block block1 = allocator.allocate(32);
    CHECK(block1.ptr != nullptr);
    CHECK(block1.size == 32);

    memory_block block2 = allocator.allocate(64);
    CHECK(block2.ptr != nullptr);
    CHECK(block2.size == 64);

    memory_block block3 = allocator.allocate(128);
    CHECK(block3.ptr != nullptr);
    CHECK(block3.size == 128);

    allocator.deallocate(block1);
    allocator.deallocate(block2);
    allocator.deallocate(block3);
}

TEST_CASE("slab_allocator allocate and deallocate objects with sizes less than slab sizes")
{
    slab_allocator<stack_allocator<1024>, 4, 32, 64, 128> allocator;

    memory_block block1 = allocator.allocate(24);
    CHECK(block1.ptr != nullptr);
    CHECK(block1.size == 24);

    memory_block block2 = allocator.allocate(48);
    CHECK(block2.ptr != nullptr);
    CHECK(block2.size == 48);

    memory_block block3 = allocator.allocate(96);
    CHECK(block3.ptr != nullptr);
    CHECK(block3.size == 96);

    allocator.deallocate(block1);
    allocator.deallocate(block2);
    allocator.deallocate(block3);
}

TEST_CASE("slab_allocator allocate nullblk with unsupported size", "[memory]")
{
    slab_allocator<stack_allocator<1024>, 4, 32, 64, 128> allocator;

    SECTION("zero")
    {
        CHECK(allocator.allocate(0) == nullblk);
    }

    SECTION("out of bounds")
    {
        CHECK(allocator.allocate(150) == nullblk);
        CHECK(allocator.allocate(256) == nullblk);
    }
}

TEST_CASE("slab_allocator deallocate nullblk", "[memory]")
{
    slab_allocator<stack_allocator<1024>, 4, 32, 64, 128> allocator;

    memory_block block = nullblk;
    allocator.deallocate(block);
    CHECK(block == nullblk);
}

TEST_CASE("slab_allocator fragmentation handling with 'random' deallocation", "[memory]")
{
    constexpr size_t allocation_count = 10;

    slab_allocator<stack_allocator<1024 * 8>, 32, 32, 64, 128> allocator;

    std::vector<size_t> indices = {3, 8, 2, 9, 4, 5, 0, 7, 1, 6};
    REQUIRE(indices.size() == allocation_count);

    // Allocate 10 blocks of 32 bytes
    std::vector<memory_block> blocks;
    blocks.reserve(allocation_count);
    for (size_t i = 0; i < allocation_count; ++i)
    {
        blocks.push_back(allocator.allocate(32));
        CHECK(blocks[i].ptr != nullptr);
    }

    // Deallocate blocks in 'random' order
    for (size_t i : indices)
    {
        allocator.deallocate(blocks[i]);
    }

    // Allocate again and ensure no issues
    for (size_t i = 0; i < allocation_count; ++i)
    {
        blocks[i] = allocator.allocate(32);
        CHECK(blocks[i].ptr != nullptr);
    }
}

TEST_CASE("slab_allocator stress test with delayed deallocation", "[memory]")
{
    slab_allocator<stack_allocator<0x1000 * 32>, 64, 32, 64> allocator;

    std::vector<memory_block> blocks;

    // Allocate 1000 blocks
    for (size_t i = 0; i < 1000; ++i)
    {
        blocks.push_back(allocator.allocate(i % 2 ? 32 : 64));
        CHECK(blocks[i].ptr != nullptr);
    }

    // Deallocate all blocks
    for (auto& block : blocks)
    {
        allocator.deallocate(block);
    }
}

} // namespace nxx
