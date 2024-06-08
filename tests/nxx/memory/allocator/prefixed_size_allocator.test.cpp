#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <nxx/memory/allocator/allocator.fixture.hpp>
#include <nxx/memory/allocator/prefixed_size_allocator.hpp>
#include <nxx/memory/allocator/stack_allocator.hpp>

namespace nxx {

using prefixed_size_allocator_fixture = allocator_fixture<prefixed_size_allocator<stack_allocator<512>>>;

TEST_CASE_METHOD(prefixed_size_allocator_fixture, "prefixed_size_allocator allocate", "[memory]")
{
    size_t size = GENERATE(4, 8, 12, 16, 32);

    memory_block block = allocator.allocate(size);

    CHECK(allocator.get_prefixed_size(block) == size);

    deallocate_and_check_is_nullblk(block);
}

TEST_CASE_METHOD(prefixed_size_allocator_fixture, "prefixed_size_allocator expand", "[memory]")
{
    size_t size = GENERATE(4, 8, 12, 16, 32);

    memory_block block = allocator.allocate(size);
    allocator.expand(block, size);

    CHECK(allocator.get_prefixed_size(block) == size * 2);

    deallocate_and_check_is_nullblk(block);
}

TEST_CASE_METHOD(prefixed_size_allocator_fixture, "prefixed_size_allocator reallocate", "[memory]")
{
    size_t size = GENERATE(4, 8, 12, 16, 32);

    memory_block block = allocator.allocate(size);
    allocator.reallocate(block, size * 2);

    CHECK(allocator.get_prefixed_size(block) == size * 2);

    deallocate_and_check_is_nullblk(block);
}

} // namespace nxx
