#include <catch2/catch_test_macros.hpp>

#include <nxxint.hpp>

namespace nxx {

TEST_CASE("int")
{   
    STATIC_CHECK(sizeof(u8_t) == 1);
    STATIC_CHECK(sizeof(s8_t) == 1);

    STATIC_CHECK(sizeof(u16_t) == 2);
    STATIC_CHECK(sizeof(s16_t) == 2);

    STATIC_CHECK(sizeof(u32_t) == 4);
    STATIC_CHECK(sizeof(s32_t) == 4);

    STATIC_CHECK(sizeof(u64_t) == 8);
    STATIC_CHECK(sizeof(s64_t) == 8);

    STATIC_CHECK(sizeof(f32_t) == 4);
    STATIC_CHECK(sizeof(f64_t) == 8);
}

} // namespace NOS