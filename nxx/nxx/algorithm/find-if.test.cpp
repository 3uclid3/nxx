#include <nxx/algorithm/find-if.hpp>

#include <catch2/catch_test_macros.hpp>

#include <nxx/container/static-array.hpp>

namespace nxx {

TEST_CASE("findIf", "[algorithm]")
{
    auto is_even = [](int v) { return (v % 2) == 0; };
    auto is_odd = [](int v) { return (v % 2) != 0; };

    static_array values = to_static_array<int>({0, 2, 4, 6});

    SECTION("iterator")
    {
        CHECK(find_if(values.begin(), values.end(), is_even) == values.begin());
        CHECK(find_if(values.begin(), values.end(), is_odd) == values.end());
    }

    SECTION("range")
    {
        CHECK(range::find_if(values, is_even) == values.begin());
        CHECK(range::find_if(values, is_odd) == values.end());
    }
}

} // namespace nxx
