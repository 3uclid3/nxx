#include <catch2/catch_test_macros.hpp>

#include <nxx/memory/utility.hpp>

namespace nxx {

TEST_CASE("memcmp", "[memory]")
{
    char mem1[5] = {'a', 'b', 'c', 'd', 'e'};
    char mem2[5] = {'a', 'b', 'c', 'd', 'e'};
    char mem3[5] = {'a', 'b', 'x', 'd', 'e'};

    CHECK(memcmp(mem1, mem2, 5) == 0);
    CHECK(memcmp(mem1, mem3, 5) != 0);
}

TEST_CASE("memcpy", "[memory]")
{
    char src[5] = {'a', 'b', 'c', 'd', 'e'};
    char dest[5];
    memcpy(dest, src, 5);

    CHECK(memcmp(src, dest, 5) == 0);
}

TEST_CASE("memset", "[memory]")
{
    char mem[5];
    memset(mem, 'x', 5);

    for (int i = 0; i < 5; ++i)
    {
        CHECK(mem[i] == 'x');
    }
}

TEST_CASE("memmove", "[memory]")
{
    char src[100] = "abcdefgh";
    memmove(src + 2, src, 6);

    CHECK(memcmp(src, "ababcdef", 8) == 0);
}

} // namespace nxx
