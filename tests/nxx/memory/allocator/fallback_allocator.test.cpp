#include <catch2/catch_test_macros.hpp>

#include <nxx/memory/allocator/allocator.fixture.hpp>
#include <nxx/memory/allocator/fallback_allocator.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

template<typename TagT>
struct mock_basic_minimal_fallback_allocator
{
    [[nodiscard]] memory_block allocate(size_t size)
    {
        NXX_UNUSED(size);
        if (!will_allocate)
        {
            return nullblk;
        }

        ++allocate_count;
        return allocate_block;
    }

    bool reallocate(memory_block& block, size_t new_size)
    {
        NXX_UNUSED(new_size);
        if (will_reallocate)
        {
            block = reallocate_block;
            ++reallocate_count;
        }
        return will_reallocate;
    }

    void deallocate(memory_block block)
    {
        if (will_deallocate)
        {
            block = nullblk;
            ++deallocate_count;
        }
    }
    static void reset_mock()
    {
        will_allocate = true;
        will_reallocate = true;
        will_deallocate = true;
        allocate_block = nullblk;
        reallocate_block = nullblk;
        allocate_count = 0;
        reallocate_count = 0;
        deallocate_count = 0;
    }

    inline static bool will_allocate{true};
    inline static bool will_reallocate{true};
    inline static bool will_deallocate{true};
    inline static memory_block allocate_block{nullblk};
    inline static memory_block reallocate_block{nullblk};
    inline static size_t allocate_count{0};
    inline static size_t reallocate_count{0};
    inline static size_t deallocate_count{0};
};

template<typename TagT>
struct mock_basic_fallback_allocator : mock_basic_minimal_fallback_allocator<TagT>
{
    using super = mock_basic_minimal_fallback_allocator<TagT>;

    [[nodiscard]] bool owns(const memory_block& block) const
    {
        NXX_UNUSED(block);
        return will_owns;
    }

    bool expand(memory_block& block, size_t delta)
    {
        NXX_UNUSED(delta);
        if (will_expand)
        {
            block = expand_block;
        }
        return will_expand;
    }

    void deallocate_all()
    {
        ++deallocate_all_count;
    }

    static void reset_mock()
    {
        super::reset_mock();

        will_owns = false;
        will_expand = true;
        expand_block = nullblk;
        expand_count = 0;
        deallocate_all_count = 0;
    }

    inline static bool will_owns{false};
    inline static bool will_expand{true};
    inline static memory_block expand_block{nullblk};
    inline static size_t expand_count{0};
    inline static size_t deallocate_all_count{0};
};

struct primary_tag
{};
struct fallback_tag
{};

using mock_fallback_allocator = fallback_allocator<mock_basic_fallback_allocator<primary_tag>, mock_basic_fallback_allocator<fallback_tag>>;

struct fallback_allocator_fixture : allocator_fixture<mock_fallback_allocator>
{
    using mock_primary = mock_basic_fallback_allocator<primary_tag>;
    using mock_fallback = mock_basic_fallback_allocator<fallback_tag>;

    fallback_allocator_fixture()
    {
        mock_primary::reset_mock();
        mock_fallback::reset_mock();
    }
};

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
