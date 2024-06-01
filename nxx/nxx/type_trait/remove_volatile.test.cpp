#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/is_same.hpp>
#include <nxx/type_trait/remove_volatile.hpp>

namespace nxx {

TEST_CASE("remove_volatile", "[type-trait]")
{
    STATIC_CHECK(is_same<remove_volatile<volatile s8_t>, s8_t>);
    STATIC_CHECK(is_same<remove_volatile<volatile u8_t>, u8_t>);
    STATIC_CHECK(is_same<remove_volatile<volatile s16_t>, s16_t>);
    STATIC_CHECK(is_same<remove_volatile<volatile u16_t>, u16_t>);

    STATIC_CHECK(is_same<remove_volatile<s8_t>, s8_t>);
    STATIC_CHECK(is_same<remove_volatile<u8_t>, u8_t>);
    STATIC_CHECK(is_same<remove_volatile<s16_t>, s16_t>);
    STATIC_CHECK(is_same<remove_volatile<u16_t>, u16_t>);
}

} // namespace nxx