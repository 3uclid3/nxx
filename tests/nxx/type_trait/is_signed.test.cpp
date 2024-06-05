#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/is_signed.hpp>

namespace nxx {

TEST_CASE("is_signed", "[type-trait]")
{
    STATIC_CHECK(is_signed<f32_t>);
    STATIC_CHECK(is_signed<f64_t>);

    STATIC_CHECK(is_signed<s8_t>);
    STATIC_CHECK(is_signed<s16_t>);
    STATIC_CHECK(is_signed<s32_t>);
    STATIC_CHECK(is_signed<s64_t>);

    STATIC_CHECK_FALSE(is_signed<u8_t>);
    STATIC_CHECK_FALSE(is_signed<u16_t>);
    STATIC_CHECK_FALSE(is_signed<u32_t>);
    STATIC_CHECK_FALSE(is_signed<u64_t>);
}

} // namespace nxx