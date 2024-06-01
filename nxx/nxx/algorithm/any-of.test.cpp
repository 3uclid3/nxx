#include <nxx/algorithm/any-of.hpp>

#include <catch2/catch_test_macros.hpp>

#include <nxx/container/static-array.hpp>

namespace nxx {

TEST_CASE("any_of", "[algorithm]")
{
    static_array values = to_static_array<int>({1, 2, 3, 3});

    auto is_two = [](int v) { return v == 2; };
    auto is_four = [](int v) { return v == 4; };

    SECTION("iterator")
    {
        CHECK(any_of(values.begin(), values.end(), is_two));
        CHECK_FALSE(any_of(values.begin(), values.end(), is_four));
    }

    SECTION("range")
    {
        CHECK(range::any_of(values, is_two));
        CHECK_FALSE(range::any_of(values, is_four));
    }
}

} // namespace nxx
