#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type-trait/decay.hpp>
#include <nxx/type-trait/is-same.hpp>
#include <nxx/utility/to-underlying.hpp>

namespace nxx {

using EnumType = u16_t;
constexpr EnumType expected_value = 42;

enum class Enum : EnumType
{
    value = expected_value
};

TEST_CASE("to_underlying")
{
    const auto value = to_underlying(Enum::value);

    STATIC_CHECK(is_same<decay<decltype(value)>, EnumType>);
    CHECK(value == expected_value);
}

} // namespace nxx
