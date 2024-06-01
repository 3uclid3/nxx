#include <catch2/catch_test_macros.hpp>

#include <nxx/container/span.hpp>
#include <nxx/container/static_array.hpp>

namespace nxx {

void check(span<int> s)
{
    REQUIRE(s.size() == 3);
    CHECK(s[0] == 1);
    CHECK(s[1] == 2);
    CHECK(s[2] == 3);
}

TEST_CASE("span")
{
    SECTION("c array")
    {
        int c[]{1, 2, 3};
        check(c);
    }

    SECTION("static_array")
    {
        static_array<int, 3> a{1, 2, 3};
        check(a);
    }
}

} // namespace nxx
