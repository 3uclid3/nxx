#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <nxx/memory/allocator/allocator.fixture.hpp>
#include <nxx/memory/allocator/allocator.mock.hpp>
#include <nxx/memory/allocator/segregator_allocator.hpp>
#include <nxx/memory/allocator/stack_allocator.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

using segregator_basic_allocators = std::tuple<
    segregator_allocator<
        stack_allocator<0x1000, 4>,
        stack_allocator<0x1001, 4>,
        32>,
    segregator_allocator<
        stack_allocator<0x1000, 8>,
        stack_allocator<0x1001, 8>,
        32>,
    segregator_allocator<
        stack_allocator<0x1000, 16>,
        stack_allocator<0x1001, 16>,
        32>>;

TEMPLATE_LIST_TEST_CASE_METHOD(basic_allocator_fixture, "segregator_allocator basics", "[memory]", segregator_basic_allocators)
{
    this->large_expand = false;
    this->unaligned_size = TestType::threshold;

    this->test_basics();
}

struct small_tag
{};
struct large_tag
{};

using mock_segregator_allocator = segregator_allocator<mock::basic_allocator<small_tag>, mock::basic_allocator<large_tag>, 32>;

struct segregator_allocator_fixture : allocator_fixture<mock_segregator_allocator>
{
    using mock_small = mock::basic_allocator<small_tag>;
    using mock_large = mock::basic_allocator<large_tag>;

    static constexpr size_t threshold = mock_segregator_allocator::threshold;

    static constexpr size_t small_threshold = threshold - 1;
    static constexpr size_t large_threshold = threshold + 1;

    segregator_allocator_fixture()
    {
        mock_small::reset_mock();
        mock_large::reset_mock();
    }
};

TEST_CASE_METHOD(segregator_allocator_fixture, "segregator_allocator allocate with small allocator", "[memory]")
{
    mock_small::allocate_block = memory_block{&allocator, small_threshold};
    memory_block block = allocator.allocate(small_threshold);

    CHECK(mock_small::allocate_block == block);
    CHECK(mock_small::allocate_count == 1);
    CHECK(mock_large::allocate_count == 0);
}
TEST_CASE_METHOD(segregator_allocator_fixture, "segregator_allocator allocate with large allocator", "[memory]")
{
    mock_large::allocate_block = memory_block{&allocator, large_threshold};
    memory_block block = allocator.allocate(large_threshold);

    CHECK(mock_large::allocate_block == block);
    CHECK(mock_large::allocate_count == 1);
    CHECK(mock_small::allocate_count == 0);
}

TEST_CASE_METHOD(segregator_allocator_fixture, "segregator_allocator deallocate nullblk is small allocator", "[memory]")
{
    memory_block block = nullblk;
    allocator.deallocate(block);

    CHECK(mock_small::deallocate_count == 1);
    CHECK(mock_large::deallocate_count == 0);

    CHECK(block == nullblk);
}

TEST_CASE_METHOD(segregator_allocator_fixture, "segregator_allocator deallocate owned by small allocator", "[memory]")
{
    mock_small::will_owns = true;
    mock_small::allocate_block = memory_block{&allocator, small_threshold};

    memory_block block = allocator.allocate(small_threshold);
    allocator.deallocate(block);

    CHECK(mock_small::allocate_count == 1);
    CHECK(mock_small::deallocate_count == 1);
    CHECK(mock_large::allocate_count == 0);
    CHECK(mock_large::deallocate_count == 0);
}

TEST_CASE_METHOD(segregator_allocator_fixture, "segregator_allocator deallocate owned by fallback allocator", "[memory]")
{
    mock_large::will_owns = true;
    mock_large::allocate_block = memory_block{&allocator, large_threshold};

    memory_block block = allocator.allocate(large_threshold);
    allocator.deallocate(block);

    CHECK(mock_large::allocate_count == 1);
    CHECK(mock_large::deallocate_count == 1);
    CHECK(mock_small::allocate_count == 0);
    CHECK(mock_small::deallocate_count == 0);
}

} // namespace nxx
