#include <catch2/catch_test_macros.hpp>

#include <nxx/type_trait/is_same.hpp>
#include <nxx/utility/integer_sequence.hpp>

namespace nxx {

TEST_CASE("make_index_sequence")
{
    STATIC_CHECK(is_same<make_index_sequence<4>, index_sequence<0, 1, 2, 3>>);
}

TEST_CASE("index_sequence_for")
{
    STATIC_CHECK(is_same<index_sequence_for<int, int, int, int>, index_sequence<0, 1, 2, 3>>);
}

} // namespace nxx
