#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type-trait/bits-of.hpp>

namespace nxx {

TEST_CASE("bits_of", "[type-trait]")
{
    STATIC_CHECK(bits_of<s8_t> == 8);
    STATIC_CHECK(bits_of<u8_t> == 8);
    STATIC_CHECK(bits_of<s16_t> == 16);
    STATIC_CHECK(bits_of<u16_t> == 16);
    STATIC_CHECK(bits_of<s32_t> == 32);
    STATIC_CHECK(bits_of<u32_t> == 32);
    STATIC_CHECK(bits_of<s64_t> == 64);
    STATIC_CHECK(bits_of<u64_t> == 64);    
    STATIC_CHECK(bits_of<f32_t> == 32);
    STATIC_CHECK(bits_of<f64_t> == 64);
}

} // namespace nxx