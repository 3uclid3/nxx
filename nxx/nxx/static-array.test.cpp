#include <catch2/catch_test_macros.hpp>

#include <nxx/static-array.hpp>

namespace nxx {

TEST_CASE("static_array::fill")
{
    static_array<int, 4> array;
    array.fill(42);

    for(int v : array)
    {
        CHECK(v == 42);
    }
}

TEST_CASE("static_array::max_size")
{
    static_array<int, 4> array;
    CHECK(array.max_size());
}

} // namespace nxx
