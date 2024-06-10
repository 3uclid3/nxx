#pragma once

#include <catch2/catch_test_macros.hpp>

#include <vector>

#include <nxx/memory/alignment.hpp>
#include <nxx/memory/allocator/allocator_traits.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

template<typename AllocatorT>
struct allocator_fixture
{
    using allocator_type = AllocatorT;

    void deallocate_and_check_is_nullblk(memory_block& block)
    {
        allocator.deallocate(block);
        CHECK(block == nullblk);
    }

    AllocatorT allocator;
};

template<typename AllocatorT>
struct basic_allocator_fixture
{
    struct scope_memory_block : memory_block
    {
        constexpr scope_memory_block(const memory_block& block)
            : memory_block{block}
        {}

        ~scope_memory_block()
        {
            if (ptr)
            {
                REQUIRE(allocator_ptr);
                allocator_ptr->deallocate(*this);
                CHECK_FALSE(*this);
            }
        }
    };

    basic_allocator_fixture()
    {
        allocator_ptr = &allocator;
    }

    ~basic_allocator_fixture()
    {
        allocator_ptr = nullptr;
    }

    void test_basic_allocate()
    {
        SECTION("allocate")
        {
            SECTION("allocate size 0 return nullblk")
            {
                scope_memory_block block = allocator.allocate(0);

                CHECK(block == nullblk);
            }

            SECTION("allocate size smaller than alignment")
            {
                scope_memory_block block = allocator.allocate(allocator.get_alignment() - 1);

                CHECK(block.ptr != nullptr);
                CHECK(block.size == allocator.get_alignment() - 1);
            }

            SECTION("allocate size of alignment")
            {
                scope_memory_block block = allocator.allocate(allocator.get_alignment());

                CHECK(block.ptr != nullptr);
                CHECK(block.size == allocator.get_alignment());
            }

            SECTION("allocate size bigger than alignment")
            {
                scope_memory_block block = allocator.allocate(allocator.get_alignment() + 1);

                CHECK(block.ptr != nullptr);
                CHECK(block.size == allocator.get_alignment() + 1);
            }
        }
    }

    void test_basic_expand()
    {
        if constexpr (allocator_traits::has_expand<AllocatorT>)
        {
            if (!small_expand && !large_expand)
            {
                return;
            }

            SECTION("expand")
            {
                if (small_expand)
                {
                    SECTION("expand size 0 does nothing")
                    {
                        scope_memory_block block = allocator.allocate(aligned_size);

                        CHECK(allocator.expand(block, 0));
                        CHECK(block.ptr != nullptr);
                        CHECK(block.size == aligned_size);
                    }

                    SECTION("expand size 0 nullblk does nothing")
                    {
                        scope_memory_block block = nullblk;

                        CHECK(allocator.expand(block, 0));
                        CHECK(block == nullblk);
                    }

                    SECTION("expand nullblk allocate")
                    {
                        scope_memory_block block = nullblk;

                        CHECK(allocator.expand(block, aligned_size));
                        CHECK(block.ptr != nullptr);
                        CHECK(block.size == aligned_size);
                    }

                    SECTION("expand size smaller than alignment to alignment")
                    {
                        scope_memory_block block = allocator.allocate(allocator.get_alignment() - 1);

                        CHECK(allocator.expand(block, 1));
                        CHECK(block.ptr != nullptr);
                        CHECK(block.size == allocator.get_alignment());
                    }

                    SECTION("expand size bigger than alignment to double alignment")
                    {
                        scope_memory_block block = allocator.allocate(allocator.get_alignment() + 1);

                        CHECK(allocator.expand(block, allocator.get_alignment() - 1));
                        CHECK(block.ptr != nullptr);
                        CHECK(block.size == allocator.get_alignment() * 2);
                    }
                }

                if (large_expand)
                {
                    SECTION("expand")
                    {
                        scope_memory_block block = nullblk;

                        for (size_t i = 0; i < 10; ++i)
                        {
                            const size_t size = i % 2 ? unaligned_size : round_to_alignment(block.size + unaligned_size, allocator.get_alignment()) - block.size;
                            const size_t expected_size = block.size + size;

                            INFO("expand #" << i << " size " << size);

                            CHECK(allocator.expand(block, size));
                            CHECK(block.ptr != nullptr);
                            CHECK(block.size == expected_size);
                        }
                    }
                }
            }
        }
    }

    void test_basic_reallocate()
    {
        SECTION("reallocate")
        {
            SECTION("reallocate size 0 deallocate")
            {
                scope_memory_block block = allocator.allocate(aligned_size);

                CHECK(allocator.reallocate(block, 0));
                CHECK(block == nullblk);
            }

            SECTION("reallocate size 0 nullblk does nothing")
            {
                scope_memory_block block = nullblk;

                CHECK(allocator.reallocate(block, 0));
                CHECK(block == nullblk);
            }

            SECTION("reallocate nullblk allocate")
            {
                scope_memory_block block = nullblk;

                CHECK(allocator.reallocate(block, aligned_size));
                CHECK(block.ptr != nullptr);
                CHECK(block.size == aligned_size);
            }

            SECTION("reallocate size smaller than alignment to alignment")
            {
                scope_memory_block block = allocator.allocate(allocator.get_alignment() - 1);

                CHECK(allocator.reallocate(block, allocator.get_alignment()));
                CHECK(block.ptr != nullptr);
                CHECK(block.size == allocator.get_alignment());
            }

            SECTION("reallocate size bigger than alignment to double alignment")
            {
                scope_memory_block block = allocator.allocate(allocator.get_alignment() + 1);

                CHECK(allocator.reallocate(block, allocator.get_alignment() * 2));
                CHECK(block.ptr != nullptr);
                CHECK(block.size == allocator.get_alignment() * 2);
            }

            SECTION("reallocate")
            {
                scope_memory_block block = nullblk;

                size_t size = 0;
                for (size_t i = 0; i < 10; ++i)
                {
                    size += unaligned_size;

                    if (i % 2)
                    {
                        size = round_to_alignment(size, allocator.get_alignment());
                    }

                    CHECK(allocator.reallocate(block, size));
                    CHECK(block.ptr != nullptr);
                    CHECK(block.size == size);
                }
            }
        }
    }

    void test_basic_deallocate()
    {
        SECTION("deallocate")
        {
            SECTION("deallocate nullblk does nothing")
            {
                memory_block block = nullblk;

                deallocate_and_check(block);
            }

            SECTION("deallocate set to nullblk")
            {
                memory_block block = allocator.allocate(aligned_size);

                deallocate_and_check(block);
            }
        }
    }

    void test_basic_deallocate_all()
    {
        if constexpr (allocator_traits::has_deallocate_all<AllocatorT>)
        {
            SECTION("deallocate_all")
            {
                for (size_t i = 0; i < 10; ++i)
                {
                    memory_block block = allocator.allocate(aligned_size);
                    NXX_UNUSED(block);
                }

                allocator.deallocate_all();
                SUCCEED();
            }
        }
    }

    void test_basic_stress()
    {
        SECTION("stress")
        {
            std::vector<scope_memory_block> allocated_blocks;
            allocated_blocks.reserve(70);

            INFO("allocate 50 blocks");
            for (size_t i = 0; i < 50; ++i)
            {
                const size_t size = i % 2 ? unaligned_size : aligned_size;
                allocated_blocks.emplace_back(allocator.allocate(size));

                CHECK(allocated_blocks.back().ptr != nullptr);
                CHECK(allocated_blocks.back().size == size);
            }

            INFO("deallocate 5 blocks");
            for (size_t i = 45; i < 50; ++i)
            {
                deallocate_and_check_is_nullblk(allocated_blocks[i]);
            }
            allocated_blocks.resize(45);

            INFO("allocate and expand 10 blocks");
            for (size_t i = 0; i < 10; ++i)
            {
                const size_t size = i % 2 ? unaligned_size : aligned_size;
                allocated_blocks.emplace_back(allocator.allocate(size));

                CHECK(allocated_blocks.back().ptr != nullptr);
                CHECK(allocated_blocks.back().size == size);

                CHECK(allocator.expand(allocated_blocks.back(), size));

                CHECK(allocated_blocks.back().ptr != nullptr);
                CHECK(allocated_blocks.back().size == size * 2);
            }

            INFO("allocate and reallocate 10 blocks");
            for (size_t i = 0; i < 10; ++i)
            {
                const size_t size = i % 2 ? unaligned_size : aligned_size;
                allocated_blocks.emplace_back(allocator.allocate(size));

                CHECK(allocated_blocks.back().ptr != nullptr);
                CHECK(allocated_blocks.back().size == size);

                CHECK(allocator.reallocate(allocated_blocks.back(), size * 2));

                CHECK(allocated_blocks.back().ptr != nullptr);
                CHECK(allocated_blocks.back().size == size * 2);
            }

            INFO("deallocate 10 blocks in reverse order");
            for (size_t i = 0; i < 10; ++i)
            {
                deallocate_and_check_is_nullblk(allocated_blocks.back());
                allocated_blocks.pop_back();
            }

            INFO("deallocate all blocks");
            for (auto& block : allocated_blocks)
            {
                deallocate_and_check_is_nullblk(block);
            }
            allocated_blocks.clear();
        }
    }

    void test_basics()
    {
        aligned_size = round_to_alignment(unaligned_size, allocator.get_alignment());

        if (aligned_size == unaligned_size)
        {
            unaligned_size -= 1;
        }

        test_basic_allocate();
        test_basic_expand();
        test_basic_reallocate();
        test_basic_deallocate();
        test_basic_deallocate_all();
    }

    void deallocate_and_check(memory_block& block)
    {
        allocator.deallocate(block);
        CHECK_FALSE(block);
    }

    AllocatorT allocator;

    // "random" size for testing
    size_t aligned_size = 42;
    size_t unaligned_size = 42;

    bool small_expand = true;
    bool large_expand = true;

    inline static AllocatorT* allocator_ptr{nullptr};
};

} // namespace nxx
