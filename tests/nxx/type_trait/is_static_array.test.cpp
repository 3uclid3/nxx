#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/is_static_array.hpp>

namespace nxx {

TEST_CASE("is_static_array", "[type_trait]")
{
    STATIC_CHECK(is_static_array<static_array<s8_t, 0>>);
    STATIC_CHECK(is_static_array<static_array<s16_t, 1>>);
    STATIC_CHECK(is_static_array<static_array<s32_t, 2>>);
    STATIC_CHECK(is_static_array<static_array<s64_t, 3>>);

    STATIC_CHECK_FALSE(is_static_array<u8_t>);
    STATIC_CHECK_FALSE(is_static_array<u16_t>);
    STATIC_CHECK_FALSE(is_static_array<u32_t>);
    STATIC_CHECK_FALSE(is_static_array<u64_t>);
}

} // namespace nxx