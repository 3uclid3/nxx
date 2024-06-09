#pragma once

#include <nxx/memory/allocator/free_list_allocator.hpp>

namespace nxx {

struct exact_fit_free_list_strategy
{
    constexpr free_list_node* allocate(free_list& list, size_t size);
    constexpr bool deallocate(free_list& list, memory_block& block);
};

constexpr free_list_node* exact_fit_free_list_strategy::allocate(free_list& list, size_t size)
{
    free_list_node* prev_node = nullptr;
    free_list_node* node = list.first_node;

    while (node)
    {
        if (node->size == size)
        {
            if (prev_node)
            {
                prev_node->next = node->next;
            }
            else
            {
                list.first_node = node->next;
            }

            node->next = nullptr;
            return node;
        }

        prev_node = node;
        node = node->next;
    }

    return nullptr;
}

constexpr bool exact_fit_free_list_strategy::deallocate(free_list& list, memory_block& block)
{
    free_list_node* node = static_cast<free_list_node*>(block.ptr);

    node->size = block.size;
    node->next = list.first_node;

    list.first_node = node;

    return true;
}

} // namespace nxx
