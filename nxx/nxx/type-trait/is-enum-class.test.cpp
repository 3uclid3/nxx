#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type-trait/is-enum-class.hpp>

namespace nxx {

enum class enum_class_a
{
    v
};
enum class enum_class_b
{
    v
};

enum enum_a
{
    enum_a_v
};

enum enum_b
{
    enum_b_v
};

TEST_CASE("is_enum_class", "[type-trait]")
{
    STATIC_CHECK(is_enum_class<enum_class_a>);
    STATIC_CHECK(is_enum_class<enum_class_b>);

    STATIC_CHECK_FALSE(is_enum_class<enum_a>);
    STATIC_CHECK_FALSE(is_enum_class<enum_b>);
    STATIC_CHECK_FALSE(is_enum_class<u32_t>);
}

} // namespace nxx