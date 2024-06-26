#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/is_base_of.hpp>

namespace nxx {

struct Fruit { };
struct Apple : Fruit { };
struct GreenApple : Apple { };
struct RedApple : Apple { };
struct Orange : Fruit { };

TEST_CASE("is_base_of", "[type_trait]")
{
    STATIC_CHECK(is_base_of<Fruit, Apple>);
    STATIC_CHECK(is_base_of<Fruit, GreenApple>);
    STATIC_CHECK(is_base_of<Fruit, RedApple>);
    STATIC_CHECK(is_base_of<Fruit, Orange>);

    STATIC_CHECK_FALSE(is_base_of<Apple, Orange>);
    STATIC_CHECK_FALSE(is_base_of<GreenApple, Apple>);
    STATIC_CHECK_FALSE(is_base_of<RedApple, Apple>);
}

} // namespace nxx