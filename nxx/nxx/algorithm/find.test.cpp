#include <nxx/algorithm/find.hpp>

#include <catch2/catch_test_macros.hpp>

#include <nxx/container/static-array.hpp>

namespace nxx {

TEST_CASE("find", "[algorithm]")
{
    static_array values = to_static_array<int>({0, 2, 4, 6});

    SECTION("iterator")
    {
        CHECK(find(values.begin(), values.end(), 0) == values.begin());
        CHECK(find(values.begin(), values.end(), 1) == values.end());
    }

    SECTION("iterator")
    {
        CHECK(range::find(values, 0) == values.begin());
        CHECK(range::find(values, 1) == values.end());
    }
}

} // namespace nxx