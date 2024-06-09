#include <catch2/catch_template_test_macros.hpp>

#include <nxx/memory/allocator/allocator.fixture.hpp>
#include <nxx/memory/allocator/free_list_allocator.hpp>
#include <nxx/memory/allocator/free_list_strategy/first_fit_free_list_strategy.hpp>
#include <nxx/memory/allocator/stack_allocator.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

using free_list_basic_allocators = std::tuple<
    free_list_allocator<stack_allocator<0x1000, 4>, first_fit_free_list_strategy>,
    free_list_allocator<stack_allocator<0x1000, 8>, first_fit_free_list_strategy>,
    free_list_allocator<stack_allocator<0x1000, 16>, first_fit_free_list_strategy>>;

TEMPLATE_LIST_TEST_CASE_METHOD(basic_allocator_fixture, "free_list_allocator basics", "[memory]", free_list_basic_allocators)
{
    this->test_basics();
}

} // namespace nxx
