#include <nxx/algorithm/all.hpp>

#include <catch2/catch_test_macros.hpp>

#include <nxx/container/static_array.hpp>

namespace nxx {

TEST_CASE("all", "[algorithm]")
{
    static_array values = to_static_array<int>({2, 2, 2, 2});

    SECTION("iterator")
    {
        CHECK(all(values.begin(), values.end(), 2));
        CHECK_FALSE(all(values.begin(), values.end(), 1));
    }

    SECTION("range")
    {
        CHECK(range::all(values, 2));
        CHECK_FALSE(range::all(values, 1));
    }
}

} // namespace nxx
