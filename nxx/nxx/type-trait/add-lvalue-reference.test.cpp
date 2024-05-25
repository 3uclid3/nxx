#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type-trait/add-lvalue-reference.hpp>
#include <nxx/type-trait/is-same.hpp>

namespace nxx {

TEST_CASE("add_lvalue_reference", "[type-trait]")
{
    static_assert(is_same<add_lvalue_reference<s32_t>, s32_t&>);
    static_assert(is_same<add_lvalue_reference<s32_t&>, s32_t&>);

    static_assert(is_same<add_lvalue_reference<f32_t>, f32_t&>);
    static_assert(is_same<add_lvalue_reference<f32_t&>, f32_t&>);
}

} // namespace nxx