#include <catch2/catch_test_macros.hpp>

#include <nxx/string/format.hpp>

namespace nxx {

TEST_CASE("format - circling buffer", "[String]")
{
    constexpr string_view expected_result = "Hello World";

    const string_view result1 = format("Hello {}", "World");
    const string_view result2 = format("{} World", "Hello");
    const string_view result3 = format("Hel{}rld", "lo Wo");

    CHECK(result1 == expected_result);
    CHECK(result2 == expected_result);
    CHECK(result3 == expected_result);

    CHECK(result1.data() != result2.data()); 
    CHECK(result1.data() != result3.data()); 
    CHECK(result2.data() != result3.data()); 
}

TEST_CASE("format - long string", "[String]")
{
    const string_view result1 = format("012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789{}", "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");

    CHECK(result1 == "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
}

} // namespace nxx
