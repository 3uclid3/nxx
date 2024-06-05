#include <nxx/algorithm/any.hpp>

#include <catch2/catch_test_macros.hpp>

#include <nxx/container/static_array.hpp>

namespace nxx {

TEST_CASE("any", "[algorithm]")
{
    static_array values = to_static_array<int>({0, 2, 4, 6});
    
    SECTION("iterator")
    {
        CHECK(any(values.begin(), values.end(), 0));
        CHECK_FALSE(any(values.begin(), values.end(), 1));
    }
    
    SECTION("range")
    {
        CHECK(range::any(values, 0));
        CHECK_FALSE(range::any(values, 1));
    }
}

} // namespace nxx
