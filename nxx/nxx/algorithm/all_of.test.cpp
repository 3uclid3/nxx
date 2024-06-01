#include <nxx/algorithm/all_of.hpp>

#include <catch2/catch_test_macros.hpp>

#include <nxx/container/static_array.hpp>

namespace nxx {

TEST_CASE("all_of", "[algorithm]")
{
    static_array values = to_static_array<int>({2, 2, 2, 2});

    auto is_two = [](int v) { return v == 2; };
    auto is_four = [](int v) { return v == 4; };

    SECTION("iterator")
    {
        CHECK(all_of(values.begin(), values.end(), is_two));
        CHECK_FALSE(all_of(values.begin(), values.end(), is_four));
    }

    SECTION("range")
    {
        CHECK(range::all_of(values, is_two));
        CHECK_FALSE(range::all_of(values, is_four));
    }
}

} // namespace nxx