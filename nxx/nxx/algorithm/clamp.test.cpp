#include <nxx/algorithm/clamp.hpp>

#include <catch2/catch_test_macros.hpp>

namespace nxx {

TEST_CASE("clamp", "[algorithm]")
{
    CHECK(clamp(-1, 0, 9) == 0);
    CHECK(clamp(4, 0, 9) == 4);
    CHECK(clamp(10, 0, 9) == 9);
}

TEST_CASE("clamp functor", "[algorithm]")
{
    auto is_less = [](int lhs, int rhs) { return lhs < rhs; };

    CHECK(clamp(-1, 0, 9, is_less) == 0);
    CHECK(clamp(4, 0, 9, is_less) == 4);
    CHECK(clamp(10, 0, 9, is_less) == 9);
}

} // namespace nxx
