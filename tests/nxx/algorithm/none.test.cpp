#include <nxx/algorithm/none.hpp>

#include <catch2/catch_test_macros.hpp>

#include <nxx/container/static_array.hpp>

namespace nxx {

TEST_CASE("none", "[algorithm]")
{
    static_array values = to_static_array<int>({1, 2, 3, 5});

    SECTION("iterator")
    {
        CHECK(none(values.begin(), values.end(), 4));
        CHECK_FALSE(none(values.begin(), values.end(), 1));
    }

    SECTION("range")
    {
        CHECK(range::none(values, 4));
        CHECK_FALSE(range::none(values, 1));
    }
}

} // namespace nxx
