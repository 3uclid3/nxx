#include <catch2/catch_test_macros.hpp>

#include <nxx/utility/source-location.hpp>

namespace nxx {

static source_location function()
{
    return source_location::current();
}

TEST_CASE("source_location")
{
    CHECK(function().line() == 9);
    CHECK(function().column() == 12);
    CHECK(function().file_name() == "../nxx/nxx/utility/source-location.test.cpp");
    CHECK(function().function_name() == "source_location nxx::function()");
}

} // namespace nxx
