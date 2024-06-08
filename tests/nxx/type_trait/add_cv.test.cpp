#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/add_cv.hpp>
#include <nxx/type_trait/is_same.hpp>

namespace nxx {

TEST_CASE("add_cv", "[type_trait]")
{
    STATIC_CHECK(is_same<add_cv<s8_t>, const volatile s8_t>);
    STATIC_CHECK(is_same<add_cv<u8_t>, const volatile u8_t>);
    STATIC_CHECK(is_same<add_cv<s16_t>, const volatile s16_t>);
    STATIC_CHECK(is_same<add_cv<u16_t>, const volatile u16_t>);

    STATIC_CHECK(is_same<add_cv<const s8_t>, const volatile s8_t>);
    STATIC_CHECK(is_same<add_cv<const u8_t>, const volatile u8_t>);
    STATIC_CHECK(is_same<add_cv<const s16_t>, const volatile s16_t>);
    STATIC_CHECK(is_same<add_cv<const u16_t>, const volatile u16_t>);

    STATIC_CHECK(is_same<add_cv<volatile s8_t>, const volatile s8_t>);
    STATIC_CHECK(is_same<add_cv<volatile u8_t>, const volatile u8_t>);
    STATIC_CHECK(is_same<add_cv<volatile s16_t>, const volatile s16_t>);
    STATIC_CHECK(is_same<add_cv<volatile u16_t>, const volatile u16_t>);

    STATIC_CHECK(is_same<add_cv<const volatile s8_t>, const volatile s8_t>);
    STATIC_CHECK(is_same<add_cv<const volatile u8_t>, const volatile u8_t>);
    STATIC_CHECK(is_same<add_cv<const volatile s16_t>, const volatile s16_t>);
    STATIC_CHECK(is_same<add_cv<const volatile u16_t>, const volatile u16_t>);
}

} // namespace nxx