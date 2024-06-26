#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/add_const.hpp>
#include <nxx/type_trait/is_same.hpp>

namespace nxx {

TEST_CASE("add_const", "[type_trait]")
{
    STATIC_CHECK(is_same<add_const<s8_t>, const s8_t>);
    STATIC_CHECK(is_same<add_const<u8_t>, const u8_t>);
    STATIC_CHECK(is_same<add_const<s16_t>, const s16_t>);
    STATIC_CHECK(is_same<add_const<u16_t>, const u16_t>);
    
    STATIC_CHECK(is_same<add_const<const s8_t>, const s8_t>);
    STATIC_CHECK(is_same<add_const<const u8_t>, const u8_t>);
    STATIC_CHECK(is_same<add_const<const s16_t>, const s16_t>);
    STATIC_CHECK(is_same<add_const<const u16_t>, const u16_t>);
}

} // namespace nxx