#pragma once

#include <nxx/def.hpp>

namespace nxx {

struct free_list;
struct free_list_node;
struct memory_block;

template<typename StrategyT, size_t MaxSizeT>
struct limited_size_free_list_strategy : private StrategyT
{
    using strategy = StrategyT;

    constexpr free_list_node* allocate(free_list& list, size_t size);
    constexpr bool deallocate(free_list& list, memory_block& block);

    size_t list_size{0};
};

template<typename StrategyT, size_t MaxSizeT>
constexpr free_list_node* limited_size_free_list_strategy<StrategyT, MaxSizeT>::allocate(free_list& list, size_t size)
{
    if (list_size == 0)
    {
        return nullptr;
    }

    free_list_node* node = strategy::allocate(list, size);

    if (node != nullptr)
    {
        --list_size;
    }

    return node;
}

template<typename StrategyT, size_t MaxSizeT>
constexpr bool limited_size_free_list_strategy<StrategyT, MaxSizeT>::deallocate(free_list& list, memory_block& block)
{
    if (list_size >= MaxSizeT)
    {
        return false;
    }

    if (!strategy::deallocate(list, block))
    {
        return false;
    }

    ++list_size;
    return true;
}

} // namespace nxx
