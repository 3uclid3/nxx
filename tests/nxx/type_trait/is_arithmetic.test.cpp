#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/is_arithmetic.hpp>

namespace nxx {

TEST_CASE("is_arithmetic", "[type-trait]")
{
    STATIC_CHECK(is_arithmetic<u8_t>);
    STATIC_CHECK(is_arithmetic<s8_t>);
    STATIC_CHECK(is_arithmetic<u16_t>);
    STATIC_CHECK(is_arithmetic<s16_t>);
    STATIC_CHECK(is_arithmetic<u32_t>);
    STATIC_CHECK(is_arithmetic<s32_t>);
    STATIC_CHECK(is_arithmetic<u64_t>);
    STATIC_CHECK(is_arithmetic<s64_t>);
    STATIC_CHECK(is_arithmetic<f32_t>);
    STATIC_CHECK(is_arithmetic<f64_t>);
}

} // namespace nxx