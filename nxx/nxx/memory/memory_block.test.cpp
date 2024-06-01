#include <catch2/catch_test_macros.hpp>

#include <nxx/container/static_array.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

template<typename T>
struct base_memory_block_fixture
{
    void test_compare()
    {
        CHECK(hello_world_block0.compare(hello_world_block1) == 0);
        CHECK(hello_world_block1.compare(hello_world_block0) == 0);

        CHECK(hello_world_block0.compare(hello_block) != 0); // null terminated
        CHECK(hello_world_block0.compare(olleh_block) != 0);
    }

    static constexpr auto hello_world_size = 12;
    static constexpr auto hello_size = 6;
    static constexpr auto olleh_size = 6;

    static_array<char, hello_world_size> hello_world_buffer0{to_static_array("hello world")};
    static_array<char, hello_world_size> hello_world_buffer1{to_static_array("hello world")};
    static_array<char, hello_size> hello_buffer{to_static_array("hello")};
    static_array<char, olleh_size> olleh_buffer{to_static_array("olleh")};

    T hello_world_block0{.pointer = hello_world_buffer0.data(), .size = hello_world_buffer0.size()};
    T hello_world_block1{.pointer = hello_world_buffer1.data(), .size = hello_world_buffer1.size()};
    T hello_block{.pointer = hello_buffer.data(), .size = hello_buffer.size()};
    T olleh_block{.pointer = olleh_buffer.data(), .size = olleh_buffer.size()};
};

using const_memory_block_fixture = base_memory_block_fixture<const_memory_block>;
using memory_block_fixture = base_memory_block_fixture<memory_block>;

TEST_CASE_METHOD(const_memory_block_fixture, "const_memory_block compare", "[memory]")
{
    test_compare();
}

TEST_CASE_METHOD(memory_block_fixture, "memory_block set", "[memory]")
{
    static_array<char, 4> buffer{0};
    memory_block block {.pointer = buffer.data(), .size = buffer.size()};

    block.set(1);

    for (char c : buffer)
    {
        CHECK(c == 1);
    }
}

TEST_CASE_METHOD(memory_block_fixture, "memory_block copy", "[memory]")
{
    static_array<char, hello_size> buffer{0};
    memory_block block {.pointer = buffer.data(), .size = buffer.size()};

    block.copy(hello_block);

    CHECK(buffer[0] == 'h');
    CHECK(buffer[1] == 'e');
    CHECK(buffer[2] == 'l');
    CHECK(buffer[3] == 'l');
    CHECK(buffer[4] == 'o');
    CHECK(buffer[5] == '\0');
}

TEST_CASE_METHOD(memory_block_fixture, "memory_block move", "[memory]")
{
    static_array<char, hello_size> buffer{0};
    memory_block block {.pointer = buffer.data(), .size = buffer.size()};

    block.move(hello_block);

    CHECK(buffer[0] == 'h');
    CHECK(buffer[1] == 'e');
    CHECK(buffer[2] == 'l');
    CHECK(buffer[3] == 'l');
    CHECK(buffer[4] == 'o');
    CHECK(buffer[5] == '\0');
}

TEST_CASE_METHOD(memory_block_fixture, "memory_block compare", "[memory]")
{
    test_compare();
}

TEST_CASE("memory_block implicit convert to const_memory_block", "[memory]")
{
    const_memory_block const_block = nullblk;

    CHECK(const_block == nullblk);
}

} // namespace nxx