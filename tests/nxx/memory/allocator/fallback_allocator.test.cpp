#include <catch2/catch_test_macros.hpp>

#include <nxx/memory/allocator/allocator.fixture.hpp>
#include <nxx/memory/allocator/allocator.mock.hpp>
#include <nxx/memory/allocator/fallback_allocator.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

struct primary_tag
{};
struct fallback_tag
{};

using mock_fallback_allocator = fallback_allocator<mock::basic_fallback_allocator<primary_tag>, mock::basic_fallback_allocator<fallback_tag>>;

struct fallback_allocator_fixture : allocator_fixture<mock_fallback_allocator>
{
    using mock_primary = mock::basic_fallback_allocator<primary_tag>;
    using mock_fallback = mock::basic_fallback_allocator<fallback_tag>;

    fallback_allocator_fixture()
    {
        mock_primary::reset_mock();
        mock_fallback::reset_mock();
    }
};

TEST_CASE_METHOD(fallback_allocator_fixture, "fallback_allocator allocate zero returns nullblk", "[memory]")
{
    mock_fallback_allocator allocator;
    memory_block block = allocator.allocate(0);

    CHECK(block == nullblk);
}

TEST_CASE_METHOD(fallback_allocator_fixture, "fallback_allocator allocate with primary allocator", "[memory]")
{
    mock_fallback_allocator allocator;
    mock_primary::allocate_block = memory_block{&allocator, sizeof(mock_fallback_allocator)};

    memory_block allocated_block = allocator.allocate(12);

    CHECK(mock_primary::allocate_block == allocated_block);
    CHECK(mock_primary::allocate_count == 1);
    CHECK(mock_fallback::allocate_count == 0);
}

TEST_CASE_METHOD(fallback_allocator_fixture, "fallback_allocator allocate with fallback allocator", "[memory]")
{
    mock_fallback_allocator allocator;
    mock_fallback::allocate_block = memory_block{&allocator, sizeof(mock_fallback_allocator)};

    memory_block allocated_block = allocator.allocate(12);

    CHECK(mock_fallback::allocate_block == allocated_block);
    CHECK(mock_fallback::allocate_count == 1);
    CHECK(mock_primary::allocate_count == 1);
}

TEST_CASE_METHOD(fallback_allocator_fixture, "fallback_allocator deallocate nullblk does nothing", "[memory]")
{
    mock_fallback_allocator allocator;
    memory_block block = nullblk;
    allocator.deallocate(block);

    CHECK(block == nullblk);
}

TEST_CASE_METHOD(fallback_allocator_fixture, "fallback_allocator deallocate owned by primary allocator", "[memory]")
{
    mock_fallback_allocator allocator;
    mock_primary::will_owns = true;
    mock_primary::allocate_block = memory_block{&allocator, sizeof(mock_fallback_allocator)};

    memory_block allocated_block = allocator.allocate(12);
    allocator.deallocate(allocated_block);

    CHECK(mock_primary::deallocate_count == 1);
    CHECK(mock_fallback::deallocate_count == 0);
}

TEST_CASE_METHOD(fallback_allocator_fixture, "fallback_allocator deallocate owned by fallback allocator", "[memory]")
{
    mock_fallback_allocator allocator;
    mock_fallback::will_owns = true;
    mock_fallback::allocate_block = memory_block{&allocator, sizeof(mock_fallback_allocator)};

    memory_block allocated_block = allocator.allocate(12);
    allocator.deallocate(allocated_block);

    CHECK(mock_fallback::deallocate_count == 1);
    CHECK(mock_primary::deallocate_count == 0);
}

} // namespace nxx
