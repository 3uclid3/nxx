#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/add_rvalue_reference.hpp>
#include <nxx/type_trait/is_same.hpp>

namespace nxx {

TEST_CASE("add_rvalue_reference", "[type-trait]")
{
    static_assert(is_same<add_rvalue_reference<s32_t>, s32_t&&>);
    static_assert(is_same<add_rvalue_reference<s32_t&&>, s32_t&&>);

    static_assert(is_same<add_rvalue_reference<f32_t>, f32_t&&>);
    static_assert(is_same<add_rvalue_reference<f32_t&&>, f32_t&&>);
}

} // namespace nxx