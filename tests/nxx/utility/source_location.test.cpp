#include <catch2/catch_test_macros.hpp>

#include <nxx/utility/source_location.hpp>

namespace nxx {

static source_location function()
{
    return source_location::current();
}

TEST_CASE("source_location")
{
    CHECK(function().line() == 9);
    CHECK(function().file_name() == "../tests/nxx/utility/source_location.test.cpp");
    
#if defined(__clang__)
    CHECK(function().column() == 12);
    CHECK(function().function_name() == "source_location nxx::function()");
#elif defined(__GNUC__)
    CHECK(function().column() == 36);
    CHECK(function().function_name() == "nxx::source_location nxx::function()");
#endif
}

} // namespace nxx
