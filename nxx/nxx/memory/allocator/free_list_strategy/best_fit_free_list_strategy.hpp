#pragma once

#include <nxx/memory/allocator/free_list_allocator.hpp>

namespace nxx {

struct best_fit_free_list_strategy
{
    constexpr free_list_node* allocate(free_list& list, size_t size);
    constexpr bool deallocate(free_list& list, memory_block& block);
};

constexpr free_list_node* best_fit_free_list_strategy::allocate(free_list& list, size_t size)
{
    free_list_node* best_prev_node = nullptr;
    free_list_node* best_node = nullptr;
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
        else if (node->size > size)
        {
            if (best_node == nullptr || node->size < best_node->size)
            {
                best_prev_node = prev_node;
                best_node = node;
            }
        }

        prev_node = node;
        node = node->next;
    }

    if (best_node)
    {
        if (best_prev_node)
        {
            best_prev_node->next = best_node->next;
        }
        else
        {
            list.first_node = best_node->next;
        }

        best_node->next = nullptr;
    }

    return best_node;
}

constexpr bool best_fit_free_list_strategy::deallocate(free_list& list, memory_block& block)
{
    free_list_node* node = static_cast<free_list_node*>(block.ptr);

    node->size = block.size;
    node->next = list.first_node;

    list.first_node = node;

    return true;
}

} // namespace nxx
