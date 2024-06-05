#include <catch2/catch_test_macros.hpp>

#include <nxx/memory/allocator/allocator.fixture.hpp>
#include <nxx/memory/allocator/stack_allocator.hpp>

namespace nxx {

using test_stack_allocator = stack_allocator<64, 4>;
using stack_allocator_fixture = allocator_fixture<test_stack_allocator>;

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator allocate returns nullblk when allocating 0 byte", "[memory]")
{
    memory_block block = allocator.allocate(0);

    CHECK(block == nullblk);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator allocate returns aligned size", "[memory]")
{
    memory_block block0 = allocator.allocate(1);
    memory_block block1 = allocator.allocate(test_stack_allocator::alignment + 1);

    CHECK(block0.ptr != nullptr);
    CHECK(block0.size == test_stack_allocator::alignment);

    CHECK(block1.ptr != nullptr);
    CHECK(block1.size == test_stack_allocator::alignment * 2);

    deallocate_and_check_is_nullblk(block0);
    deallocate_and_check_is_nullblk(block1);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator allocate can allocate all stack", "[memory]")
{
    memory_block block = allocator.allocate(test_stack_allocator::max_size);

    CHECK(block.ptr != nullptr);
    CHECK(block.size == test_stack_allocator::max_size);

    deallocate_and_check_is_nullblk(block);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator allocate returns nullblk when request size is > available size", "[memory]")
{
    memory_block block = allocator.allocate(test_stack_allocator::max_size + 1);
    CHECK(block == nullblk);

    block = allocator.allocate(1);
    REQUIRE(block);

    memory_block next_block = allocator.allocate(test_stack_allocator::max_size);
    CHECK(next_block == nullblk);

    deallocate_and_check_is_nullblk(block);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator allocate returns nullblk when out of memory", "[memory]")
{
    memory_block block = allocator.allocate(test_stack_allocator::max_size);
    REQUIRE(block != nullblk);

    memory_block next_block = allocator.allocate(1);
    CHECK(next_block == nullblk);

    deallocate_and_check_is_nullblk(block);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator allocate reuse last deallocated if it was the most recent allocation", "[memory]")
{
    memory_block block0 = allocator.allocate(8);
    memory_block block1 = allocator.allocate(8);

    auto ptr1 = block1.ptr;
    deallocate_and_check_is_nullblk(block1);

    memory_block block2 = allocator.allocate(8);
    CHECK(block2.ptr == ptr1);

    deallocate_and_check_is_nullblk(block0);
    deallocate_and_check_is_nullblk(block2);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator allocate dot no reuse last deallocated if it was not the most recent allocation", "[memory]")
{
    memory_block block0 = allocator.allocate(8);
    memory_block block1 = allocator.allocate(8);

    auto ptr0 = block0.ptr;
    deallocate_and_check_is_nullblk(block0);

    memory_block block2 = allocator.allocate(8);
    CHECK(block2.ptr != ptr0);

    deallocate_and_check_is_nullblk(block1);
    deallocate_and_check_is_nullblk(block2);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator reallocate increase current allocation if its the most recent allocation", "[memory]")
{
    memory_block block = allocator.allocate(4);
    *static_cast<u32_t*>(block.ptr) = 42;

    memory_block pre_realloc_block = block;
    CHECK(allocator.reallocate(block, 8));

    CHECK(block.ptr == pre_realloc_block.ptr);
    CHECK(block.size == 8);
    CHECK(*static_cast<u32_t*>(block.ptr) == 42);

    deallocate_and_check_is_nullblk(block);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator reallocate increase allocate a new block if its not the most recent allocation", "[memory]")
{
    memory_block block = allocator.allocate(4);
    *static_cast<u32_t*>(block.ptr) = 42;

    memory_block second_block = allocator.allocate(4);
    *static_cast<u32_t*>(second_block.ptr) = 69;

    memory_block pre_realloc_block = block;
    CHECK(allocator.reallocate(block, 8));

    CHECK(block.ptr != pre_realloc_block.ptr);
    CHECK(block.size == 8);
    CHECK(*static_cast<u32_t*>(block.ptr) == 42);
    CHECK(*static_cast<u32_t*>(second_block.ptr) == 69);

    deallocate_and_check_is_nullblk(block);
    deallocate_and_check_is_nullblk(second_block);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator reallocate fail when out of memory", "[memory]")
{
    memory_block block = allocator.allocate(test_stack_allocator::max_size);

    memory_block pre_realloc_block = block;
    CHECK_FALSE(allocator.reallocate(block, test_stack_allocator::max_size + 1));

    CHECK(block == pre_realloc_block);

    deallocate_and_check_is_nullblk(block);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator reallocate decrease current allocation if its the most recent allocation", "[memory]")
{
    memory_block block = allocator.allocate(8);
    *static_cast<u32_t*>(block.ptr) = 42;

    memory_block pre_realloc_block = block;
    CHECK(allocator.reallocate(block, 4));

    CHECK(block.ptr == pre_realloc_block.ptr);
    CHECK(block.size == 4);
    CHECK(*static_cast<u32_t*>(block.ptr) == 42);

    deallocate_and_check_is_nullblk(block);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator reallocate decrease current allocation if its not the most recent allocation", "[memory]")
{
    memory_block block = allocator.allocate(8);
    *static_cast<u32_t*>(block.ptr) = 42;

    memory_block second_block = allocator.allocate(4);
    *static_cast<u32_t*>(second_block.ptr) = 69;

    memory_block pre_realloc_block = block;
    CHECK(allocator.reallocate(block, 4));

    CHECK(block.ptr == pre_realloc_block.ptr);
    CHECK(block.size == 4);
    CHECK(*static_cast<u32_t*>(block.ptr) == 42);
    CHECK(*static_cast<u32_t*>(second_block.ptr) == 69);

    deallocate_and_check_is_nullblk(block);
    deallocate_and_check_is_nullblk(second_block);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator expand nullblk by 0 returns true", "[memory]")
{
    memory_block block = nullblk;
    CHECK(allocator.expand(block, 0));
    CHECK(block == nullblk);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator expand by 0 returns same block", "[memory]")
{
    memory_block block = allocator.allocate(8);
    memory_block pre_expand_block = block;

    CHECK(allocator.expand(block, 0));
    CHECK(block == pre_expand_block);

    deallocate_and_check_is_nullblk(block);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator expand nullblk by non-zero allocate a new block", "[memory]")
{
    memory_block block = nullblk;
    CHECK(allocator.expand(block, 4));
    CHECK(block.ptr != nullptr);
    CHECK(block.size == 4);
}

TEST_CASE_METHOD(stack_allocator_fixture, "stack_allocator expand over capacity returns false", "[memory]")
{
    memory_block block = nullblk;
    CHECK_FALSE(allocator.expand(block, test_stack_allocator::max_size + 1));
    CHECK(block == nullblk);

    block = allocator.allocate(4);

    memory_block pre_expand_block = block;
    CHECK_FALSE(allocator.expand(block, test_stack_allocator::max_size + 1));
    CHECK(block == pre_expand_block);

    deallocate_and_check_is_nullblk(block);
}

} // namespace nxx