#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/is_integral.hpp>

namespace nxx {

TEST_CASE("is_integral", "[type_trait]")
{
    STATIC_CHECK(is_integral<u8_t>);
    STATIC_CHECK(is_integral<s8_t>);

    STATIC_CHECK(is_integral<u16_t>);
    STATIC_CHECK(is_integral<s16_t>);

    STATIC_CHECK(is_integral<u32_t>);
    STATIC_CHECK(is_integral<s32_t>);

    STATIC_CHECK(is_integral<u64_t>);
    STATIC_CHECK(is_integral<s64_t>);

    STATIC_CHECK_FALSE(is_integral<f32_t>);
    STATIC_CHECK_FALSE(is_integral<f64_t>);
}

} // namespace nxx