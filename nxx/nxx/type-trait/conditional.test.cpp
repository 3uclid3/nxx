#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type-trait/conditional.hpp>
#include <nxx/type-trait/is-same.hpp>

namespace nxx {

TEST_CASE("conditional", "[type-trait]")
{
    STATIC_CHECK(is_same<conditional<true, u8_t, s8_t>, u8_t>);
    STATIC_CHECK(is_same<conditional<false, u8_t, s8_t>, s8_t>);
}

} // namespace nxx