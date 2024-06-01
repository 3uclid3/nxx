#include <catch2/catch_test_macros.hpp>

#include <nxx/memory/allocator/fallback_allocator.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

struct mock_primary_allocator
{
    [[nodiscard]] bool owns(const_memory_block block) const
    {
        NXX_UNUSED(block);
        return owns_mock;
    }
    [[nodiscard]] memory_block allocate(size_t size)
    {
        NXX_UNUSED(size);
        ++allocate_count;
        return alloc_block;
    }
    void deallocate(memory_block block)
    {
        NXX_UNUSED(block);
        ++deallocate_count;
    }

    inline static bool owns_mock{false};
    inline static memory_block alloc_block{nullblk};
    inline static size_t allocate_count{0};
    inline static size_t deallocate_count{0};
};

struct mock_secondary_allocator
{
    [[nodiscard]] bool owns(const_memory_block block) const
    {
        NXX_UNUSED(block);
        return owns_mock;
    }
    [[nodiscard]] memory_block allocate(size_t size)
    {
        NXX_UNUSED(size);
        ++allocate_count;
        return alloc_block;
    }
    void deallocate(memory_block block)
    {
        NXX_UNUSED(block);
        ++deallocate_count;
    }

    inline static bool owns_mock{false};
    inline static memory_block alloc_block{nullblk};
    inline static size_t allocate_count{0};
    inline static size_t deallocate_count{0};
};

using mock_fallback_allocator = fallback_allocator<mock_primary_allocator, mock_secondary_allocator>;

struct fallback_allocator_fixture
{
    fallback_allocator_fixture()
    {
        mock_primary_allocator::owns_mock = false;
        mock_primary_allocator::alloc_block = nullblk;
        mock_primary_allocator::allocate_count = 0;
        mock_primary_allocator::deallocate_count = 0;

       mock_secondary_allocator::owns_mock = false;
       mock_secondary_allocator::alloc_block = nullblk;
       mock_secondary_allocator::allocate_count = 0;
       mock_secondary_allocator::deallocate_count = 0;
    }
};

TEST_CASE_METHOD(fallback_allocator_fixture, "fallback_allocator allocate with primary allocator", "[memory]")
{
    mock_fallback_allocator allocator;
    mock_primary_allocator::alloc_block = {.pointer = &allocator, .size = sizeof(mock_fallback_allocator)};

    memory_block allocated_block = allocator.allocate(12);

    CHECK(mock_primary_allocator::alloc_block == allocated_block);
    CHECK(mock_primary_allocator::allocate_count == 1);
    CHECK(mock_secondary_allocator::allocate_count == 0);
}

TEST_CASE_METHOD(fallback_allocator_fixture, "fallback_allocator allocate with fallback allocator", "[memory]")
{
    mock_fallback_allocator allocator;
    mock_secondary_allocator::alloc_block = {.pointer = &allocator, .size = sizeof(mock_fallback_allocator)};

    memory_block allocated_block = allocator.allocate(12);

    CHECK(mock_secondary_allocator::alloc_block == allocated_block);
    CHECK(mock_secondary_allocator::allocate_count == 1);
    CHECK(mock_primary_allocator::allocate_count == 1);
}

TEST_CASE_METHOD(fallback_allocator_fixture, "fallback_allocator deallocate owned by primary allocator", "[memory]")
{
    mock_fallback_allocator allocator;
    mock_primary_allocator::owns_mock = true;
    mock_primary_allocator::alloc_block = {.pointer = &allocator, .size = sizeof(mock_fallback_allocator)};

    memory_block allocated_block = allocator.allocate(12);
    allocator.deallocate(allocated_block);

    CHECK(mock_primary_allocator::deallocate_count == 1);
    CHECK(mock_secondary_allocator::deallocate_count == 0);
}

TEST_CASE_METHOD(fallback_allocator_fixture, "fallback_allocator deallocate owned by fallback allocator", "[memory]")
{
    mock_fallback_allocator allocator;
    mock_secondary_allocator::owns_mock = true;
    mock_secondary_allocator::alloc_block = {.pointer = &allocator, .size = sizeof(mock_fallback_allocator)};

    memory_block allocated_block = allocator.allocate(12);
    allocator.deallocate(allocated_block);

    CHECK(mock_secondary_allocator::deallocate_count == 1);
    CHECK(mock_primary_allocator::deallocate_count == 0);
}

} // namespace nxx
