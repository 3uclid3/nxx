#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type-trait/decay.hpp>
#include <nxx/type-trait/is-same.hpp>

namespace nxx {

TEST_CASE("decay", "[type-trait]")
{
    STATIC_CHECK(is_same<decay<const volatile u8_t&>, u8_t>);
    STATIC_CHECK(is_same<decay<const u8_t&>, u8_t>);
    STATIC_CHECK(is_same<decay<volatile u8_t&>, u8_t>);
    STATIC_CHECK(is_same<decay<u8_t&&>, u8_t>);
    STATIC_CHECK(is_same<decay<u8_t&>, u8_t>);
    STATIC_CHECK(is_same<decay<u8_t>, u8_t>);
    
    STATIC_CHECK(is_same<decay<u8_t*&&>, u8_t*>);
    STATIC_CHECK(is_same<decay<u8_t*&>, u8_t*>);
    STATIC_CHECK(is_same<decay<u8_t*>, u8_t*>);
}

} // namespace nxx