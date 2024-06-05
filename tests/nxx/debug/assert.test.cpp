#include <catch2/catch_test_macros.hpp>

#include <nxx/debug/assert.hpp>

namespace nxx {

TEST_CASE("assert")
{
    NXX_ASSERT(true);
    NXX_ASSERT(true, "message");

    SUCCEED();
}

} // namespace nxx