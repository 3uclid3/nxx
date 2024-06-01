#include <nxx/algorithm/none-of.hpp>

#include <catch2/catch_test_macros.hpp>

#include <nxx/container/static-array.hpp>

namespace nxx {

TEST_CASE("none_of", "[algorithm]")
{
    static_array values = to_static_array<int>({1, 1, 3, 4});

    auto is_two = [](int v) { return v == 2; };
    auto is_four = [](int v) { return v == 4; };

    SECTION("iterator")
    {
        CHECK(none_of(values.begin(), values.end(), is_two));
        CHECK_FALSE(none_of(values.begin(), values.end(), is_four));
    }

    SECTION("range")
    {
        CHECK(range::none_of(values, is_two));
        CHECK_FALSE(range::none_of(values, is_four));
    }
}

} // namespace nxx
