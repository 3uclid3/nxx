#include <nxx/utility/on-scope-exit.hpp>

#include <catch2/catch_test_macros.hpp>
#include <nxx/def.hpp>

namespace nxx {

TEST_CASE("on_scope_exit", "[utility]")
{
    size_t count = 0;

    {
        auto scope = make_on_scope_exit([&count]() { ++count; });
    }

    CHECK(count == 1);
}

} // namespace nxx