#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type-trait/is-enum.hpp>

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

TEST_CASE("is_enum", "[type-trait]")
{
    STATIC_CHECK(is_enum<enum_class_a>);
    STATIC_CHECK(is_enum<enum_class_b>);
    STATIC_CHECK(is_enum<enum_a>);
    STATIC_CHECK(is_enum<enum_b>);

    STATIC_CHECK_FALSE(is_enum<u32_t>);
}

} // namespace nxx