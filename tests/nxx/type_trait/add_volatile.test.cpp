#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/add_volatile.hpp>
#include <nxx/type_trait/is_same.hpp>

namespace nxx {

TEST_CASE("add_volatile", "[type_trait]")
{
    STATIC_CHECK(is_same<add_volatile<s8_t>, volatile s8_t>);
    STATIC_CHECK(is_same<add_volatile<u8_t>, volatile u8_t>);
    STATIC_CHECK(is_same<add_volatile<s16_t>, volatile s16_t>);
    STATIC_CHECK(is_same<add_volatile<u16_t>, volatile u16_t>);
    
    STATIC_CHECK(is_same<add_volatile<volatile s8_t>, volatile s8_t>);
    STATIC_CHECK(is_same<add_volatile<volatile u8_t>, volatile u8_t>);
    STATIC_CHECK(is_same<add_volatile<volatile s16_t>, volatile s16_t>);
    STATIC_CHECK(is_same<add_volatile<volatile u16_t>, volatile u16_t>);
}

} // namespace nxx