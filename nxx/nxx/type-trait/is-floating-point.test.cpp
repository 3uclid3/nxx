#include <catch2/catch_test_macros.hpp>

#include <nxx/type-trait/is-floating-point.hpp>

namespace nxx {

TEST_CASE("is_floating_point", "[type-trait]")
{   
    STATIC_CHECK_FALSE(is_floating_point<u8_t>);
    STATIC_CHECK_FALSE(is_floating_point<s8_t>);
    
    STATIC_CHECK_FALSE(is_floating_point<u16_t>);
    STATIC_CHECK_FALSE(is_floating_point<s16_t>);
    
    STATIC_CHECK_FALSE(is_floating_point<u32_t>);
    STATIC_CHECK_FALSE(is_floating_point<s32_t>);
    
    STATIC_CHECK_FALSE(is_floating_point<u64_t>);
    STATIC_CHECK_FALSE(is_floating_point<s64_t>);
    
    STATIC_CHECK(is_floating_point<f32_t>);
    STATIC_CHECK(is_floating_point<f64_t>);
}

} // namespace NOS