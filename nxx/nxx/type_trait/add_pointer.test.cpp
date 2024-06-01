#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/add_pointer.hpp>
#include <nxx/type_trait/is_same.hpp>

namespace nxx {

TEST_CASE("add_pointer", "[type-trait]")
{
    STATIC_CHECK(is_same<add_pointer<s8_t>, s8_t*>);
    STATIC_CHECK(is_same<add_pointer<const u8_t>, const u8_t*>);
    STATIC_CHECK(is_same<add_pointer<s16_t>, s16_t*>);
    STATIC_CHECK(is_same<add_pointer<const u16_t>, const u16_t*>);
}

} // namespace nxx