#include <catch2/catch_test_macros.hpp>

#include <nxx/algorithm/max.hpp>

namespace nxx {

TEST_CASE("max", "[algorithm]")
{
    CHECK(max(0, 1) == 1);
    CHECK(max(1, 0) == 1);

    CHECK(max(0, -1) == 0);
    CHECK(max(-1, 0) == 0);

    CHECK(max('a', 'z') == 'z');
    CHECK(max('z', 'a') == 'z');
}

} // namespace nxx
