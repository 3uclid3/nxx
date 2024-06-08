#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/is_same.hpp>

namespace nxx {

TEST_CASE("is_same", "[type_trait]")
{
    STATIC_CHECK(is_same<s8_t, s8_t>);
    STATIC_CHECK(is_same<u8_t, u8_t>);
    STATIC_CHECK(is_same<s16_t, s16_t>);
    STATIC_CHECK(is_same<u16_t, u16_t>);

    STATIC_CHECK_FALSE(is_same<s8_t, u8_t>);
    STATIC_CHECK_FALSE(is_same<u8_t, s8_t>);
    STATIC_CHECK_FALSE(is_same<s16_t, u16_t>);
    STATIC_CHECK_FALSE(is_same<u16_t, s16_t>);
    STATIC_CHECK_FALSE(is_same<u8_t, u16_t>);
    STATIC_CHECK_FALSE(is_same<u16_t, u8_t>);
}

} // namespace nxx