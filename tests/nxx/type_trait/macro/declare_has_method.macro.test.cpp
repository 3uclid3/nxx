#include <catch2/catch_test_macros.hpp>

#include <nxx/type_trait/macro/declare_has_method.macro.hpp>

namespace nxx {

struct class_with_method_a
{
    void method_a(int, int) {}
    void method_a_const(int, int) const {}
};

struct class_with_no_method
{
};

NXX_TYPE_TRAIT_HAS_METHOD(has_method_a, method_a, void, int, int);
NXX_TYPE_TRAIT_HAS_METHOD_CONST(has_method_a_const, method_a_const, void, int, int);

TEST_CASE("NXX_TYPE_TRAIT_HAS_METHOD", "[macro][type-trait]")
{
    STATIC_CHECK(has_method_a<class_with_method_a>);
    STATIC_CHECK_FALSE(has_method_a<class_with_no_method>);
    
    STATIC_CHECK(has_method_a_const<class_with_method_a>);
    STATIC_CHECK_FALSE(has_method_a_const<class_with_no_method>);
}

} // namespace nxx