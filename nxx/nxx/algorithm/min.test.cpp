#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/algorithm/min.hpp>

namespace nxx {

TEST_CASE("min", "[algorithm]")
{   
    CHECK(min(0, 1) == 0);
    CHECK(min(1, 0) == 0);

    CHECK(min(0, -1) == -1);
    CHECK(min(-1, 0) == -1);
    
    CHECK(min('a', 'z') == 'a');
    CHECK(min('z', 'a') == 'a');
}

} // namespace NOS