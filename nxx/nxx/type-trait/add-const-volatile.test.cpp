#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type-trait/add-const-volatile.hpp>
#include <nxx/type-trait/is-same.hpp>

namespace nxx {

TEST_CASE("add_const_volatile", "[type-trait]")
{
    STATIC_CHECK(is_same<add_const_volatile<s8_t>, const volatile s8_t>);
    STATIC_CHECK(is_same<add_const_volatile<u8_t>, const volatile u8_t>);
    STATIC_CHECK(is_same<add_const_volatile<s16_t>, const volatile s16_t>);
    STATIC_CHECK(is_same<add_const_volatile<u16_t>, const volatile u16_t>);

    STATIC_CHECK(is_same<add_const_volatile<const s8_t>, const volatile s8_t>);
    STATIC_CHECK(is_same<add_const_volatile<const u8_t>, const volatile u8_t>);
    STATIC_CHECK(is_same<add_const_volatile<const s16_t>, const volatile s16_t>);
    STATIC_CHECK(is_same<add_const_volatile<const u16_t>, const volatile u16_t>);

    STATIC_CHECK(is_same<add_const_volatile<volatile s8_t>, const volatile s8_t>);
    STATIC_CHECK(is_same<add_const_volatile<volatile u8_t>, const volatile u8_t>);
    STATIC_CHECK(is_same<add_const_volatile<volatile s16_t>, const volatile s16_t>);
    STATIC_CHECK(is_same<add_const_volatile<volatile u16_t>, const volatile u16_t>);

    STATIC_CHECK(is_same<add_const_volatile<const volatile s8_t>, const volatile s8_t>);
    STATIC_CHECK(is_same<add_const_volatile<const volatile u8_t>, const volatile u8_t>);
    STATIC_CHECK(is_same<add_const_volatile<const volatile s16_t>, const volatile s16_t>);
    STATIC_CHECK(is_same<add_const_volatile<const volatile u16_t>, const volatile u16_t>);
}

} // namespace nxx