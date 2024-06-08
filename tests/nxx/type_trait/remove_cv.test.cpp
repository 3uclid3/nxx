#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/is_same.hpp>
#include <nxx/type_trait/remove_cv.hpp>

namespace nxx {

TEST_CASE("remove_cv", "[type_trait]")
{
    STATIC_CHECK(is_same<remove_cv<s8_t>, s8_t>);
    STATIC_CHECK(is_same<remove_cv<u8_t>, u8_t>);
    STATIC_CHECK(is_same<remove_cv<s16_t>, s16_t>);
    STATIC_CHECK(is_same<remove_cv<u16_t>, u16_t>);

    STATIC_CHECK(is_same<remove_cv<const s8_t>, s8_t>);
    STATIC_CHECK(is_same<remove_cv<const u8_t>, u8_t>);
    STATIC_CHECK(is_same<remove_cv<const s16_t>, s16_t>);
    STATIC_CHECK(is_same<remove_cv<const u16_t>, u16_t>);

    STATIC_CHECK(is_same<remove_cv<volatile s8_t>, s8_t>);
    STATIC_CHECK(is_same<remove_cv<volatile u8_t>, u8_t>);
    STATIC_CHECK(is_same<remove_cv<volatile s16_t>, s16_t>);
    STATIC_CHECK(is_same<remove_cv<volatile u16_t>, u16_t>);

    STATIC_CHECK(is_same<remove_cv<const volatile s8_t>, s8_t>);
    STATIC_CHECK(is_same<remove_cv<const volatile u8_t>, u8_t>);
    STATIC_CHECK(is_same<remove_cv<const volatile s16_t>, s16_t>);
    STATIC_CHECK(is_same<remove_cv<const volatile u16_t>, u16_t>);
}

} // namespace nxx