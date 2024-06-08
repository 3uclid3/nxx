#include <catch2/catch_test_macros.hpp>

#include <nxx/type_trait/is_const.hpp>

namespace nxx {

TEST_CASE("is_const", "[type_trait]")
{
    STATIC_CHECK(is_const<const char>);

    STATIC_CHECK_FALSE(is_const<char>);
}

} // namespace nxx