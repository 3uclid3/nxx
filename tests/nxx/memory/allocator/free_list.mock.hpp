#pragma once

#include <nxx/container/static_array.hpp>
#include <nxx/memory/allocator/free_list_allocator.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx::mock {

struct free_list : nxx::free_list
{
    constexpr memory_block new_node_block(size_t size)
    {
        return memory_block{new_node(size), size};
    }

    constexpr free_list_node* new_node(size_t size)
    {
        NXX_ASSERT(used_size < nodes.size());
        free_list_node* node = &nodes[used_size++];
        node->size = size;
        node->next = nullptr;
        return node;
    }

    constexpr free_list_node* add_node(size_t size)
    {
        free_list_node* node = new_node(size);

        if (last_node == nullptr)
        {
            first_node = node;
            last_node = node;
        }
        else
        {
            NXX_ASSERT(last_node->next == nullptr);
            last_node->next = node;
            last_node = node;
        }

        return node;
    }

    static_array<free_list_node, 32> nodes{};
    size_t used_size{0};
    free_list_node* last_node{nullptr};
};

} // namespace nxx::mock
