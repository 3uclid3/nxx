#include <catch2/catch_template_test_macros.hpp>

#include <tuple>

#include <nxx/algorithm/iota.hpp>
#include <nxx/container/static_array.hpp>
#include <nxx/type_trait/is_signed_integer.hpp>

namespace nxx {

using types = std::tuple<s8_t, s16_t, s32_t, s64_t, u8_t, u16_t, u32_t, u64_t>;

TEMPLATE_LIST_TEST_CASE("iota", "[algorithm]", types)
{
    static_array values = to_static_array<TestType>({0, 0, 0, 0});

    auto check = [&values](TestType offset) {
        for (size_t i = 0; i < values.size(); ++i)
        {
            CHECK(values[i] == offset + static_cast<TestType>(i));
        }
    };

    SECTION("iterator")
    {
        iota(values.begin(), values.end(), 0);
        check(0);
        
        iota(values.begin(), values.end(), 2);
        check(2);

        if constexpr (is_signed_integer<TestType>)
        {
            iota(values.begin(), values.end(), -2);
            check(-2);
        }
    }

    SECTION("range")
    {
        range::iota(values, 0);
        check(0);
        
        iota(values.begin(), values.end(), 2);
        check(2);

        if constexpr (is_signed_integer<TestType>)
        {
            range::iota(values, -2);
            check(-2);
        }
    }
}

} // namespace nxx