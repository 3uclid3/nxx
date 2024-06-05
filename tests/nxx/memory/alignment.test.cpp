#include <nxx/memory/alignment.hpp>

#include <catch2/catch_test_macros.hpp>

namespace nxx {

TEST_CASE("align_down", "[alignment]")
{
    REQUIRE(align_down(10, 4) == 8);   // Align 10 down to the nearest multiple of 4
    REQUIRE(align_down(15, 8) == 8);   // Align 15 down to the nearest multiple of 8
    REQUIRE(align_down(32, 16) == 32); // Align 32 down to the nearest multiple of 16
    REQUIRE(align_down(0, 8) == 0);    // Align 0 down to the nearest multiple of 8
}

TEST_CASE("align_up", "[alignment]")
{
    REQUIRE(align_up(10, 4) == 12);  // Align 10 up to the nearest multiple of 4
    REQUIRE(align_up(15, 8) == 16);  // Align 15 up to the nearest multiple of 8
    REQUIRE(align_up(32, 16) == 32); // Align 32 up to the nearest multiple of 16
    REQUIRE(align_up(0, 8) == 0);    // Align 0 up to the nearest multiple of 8
}

} // namespace nxx
