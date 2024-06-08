#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/is_same.hpp>
#include <nxx/type_trait/remove_const.hpp>

namespace nxx {

TEST_CASE("remove_const", "[type_trait]")
{
    STATIC_CHECK(is_same<remove_const<const s8_t>, s8_t>);
    STATIC_CHECK(is_same<remove_const<const u8_t>, u8_t>);
    STATIC_CHECK(is_same<remove_const<const s16_t>, s16_t>);
    STATIC_CHECK(is_same<remove_const<const u16_t>, u16_t>);

    STATIC_CHECK(is_same<remove_const<s8_t>, s8_t>);
    STATIC_CHECK(is_same<remove_const<u8_t>, u8_t>);
    STATIC_CHECK(is_same<remove_const<s16_t>, s16_t>);
    STATIC_CHECK(is_same<remove_const<u16_t>, u16_t>);
}

} // namespace nxx