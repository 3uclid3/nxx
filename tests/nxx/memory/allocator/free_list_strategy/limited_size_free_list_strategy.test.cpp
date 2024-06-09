#include <catch2/catch_test_macros.hpp>

#include <nxx/memory/allocator/free_list.mock.hpp>
#include <nxx/memory/allocator/free_list_strategy/first_fit_free_list_strategy.hpp>
#include <nxx/memory/allocator/free_list_strategy/limited_size_free_list_strategy.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

TEST_CASE("limited_size_free_list_strategy allocate", "[memory]")
{
    limited_size_free_list_strategy<first_fit_free_list_strategy, 1> strategy;
    strategy.list_size = 1;

    mock::free_list list;
    list.add_node(10);

    free_list_node* node = strategy.allocate(list, 10);

    REQUIRE(node != nullptr);
    CHECK(node->size == 10);
    CHECK(node->next == nullptr);

    CHECK(strategy.allocate(list, 10) == nullptr);
}

TEST_CASE("limited_size_free_list_strategy deallocate", "[memory]")
{
    limited_size_free_list_strategy<first_fit_free_list_strategy, 1> strategy;

    mock::free_list list;

    memory_block block = list.new_node_block(8);
    CHECK(strategy.deallocate(list, block));

    block = list.new_node_block(8);
    CHECK_FALSE(strategy.deallocate(list, block));
}

} // namespace nxx
