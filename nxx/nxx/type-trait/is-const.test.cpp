#include <catch2/catch_test_macros.hpp>

#include <nxx/type-trait/is-const.hpp>

namespace nxx {

TEST_CASE("is_const", "[type-trait]")
{
    STATIC_CHECK(is_const<const char>);

    STATIC_CHECK_FALSE(is_const<char>);
}

} // namespace nxx