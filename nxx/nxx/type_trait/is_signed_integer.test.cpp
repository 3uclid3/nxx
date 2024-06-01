#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/is_signed_integer.hpp>

namespace nxx {

TEST_CASE("is_signed_integer", "[type-trait]")
{
    STATIC_CHECK(is_signed_integer<s8_t>);
    STATIC_CHECK(is_signed_integer<s16_t>);
    STATIC_CHECK(is_signed_integer<s32_t>);
    STATIC_CHECK(is_signed_integer<s64_t>);

    STATIC_CHECK_FALSE(is_signed_integer<u8_t>);
    STATIC_CHECK_FALSE(is_signed_integer<u16_t>);
    STATIC_CHECK_FALSE(is_signed_integer<u32_t>);
    STATIC_CHECK_FALSE(is_signed_integer<u64_t>);

    STATIC_CHECK_FALSE(is_signed_integer<f32_t>);
    STATIC_CHECK_FALSE(is_signed_integer<f64_t>);
}

} // namespace nxx