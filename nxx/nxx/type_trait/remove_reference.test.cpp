#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/is_same.hpp>
#include <nxx/type_trait/remove_reference.hpp>

namespace nxx {

TEST_CASE("remove_reference", "[type-trait]")
{
    static_assert(is_same<remove_reference<s32_t>, s32_t>);
    static_assert(is_same<remove_reference<s32_t&>, s32_t>);

    static_assert(is_same<remove_reference<f32_t>, f32_t>);
    static_assert(is_same<remove_reference<f32_t&>, f32_t>);
}

} // namespace nxx