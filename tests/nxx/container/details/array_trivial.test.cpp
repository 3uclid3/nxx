#include <catch2/catch_template_test_macros.hpp>

#include <tuple>

#include <nxx/algorithm/iota.hpp>
#include <nxx/container/details/array_trivial.hpp>

namespace nxx::details {

using array_trivial_types = std::tuple<
    array_trivial<u8_t, u32_t>,
    array_trivial<u8_t, u64_t>,

    array_trivial<u16_t, u32_t>,
    array_trivial<u16_t, u64_t>,

    array_trivial<u64_t, u32_t>,
    array_trivial<u64_t, u64_t>>;

TEMPLATE_LIST_TEST_CASE("array_trivial prepend", "[container]", array_trivial_types)
{
    using value_type = typename TestType::value_type;

    TestType array;

    for (value_type i = 0; i < 150; ++i)
    {
        array.prepend(i);

        REQUIRE(array.size() == static_cast<size_t>(i + 1));

        for (value_type j = 0; j <= i; ++j)
        {
            CHECK(array[static_cast<size_t>(j)] == i - j);
        }
    }
}

TEMPLATE_LIST_TEST_CASE("array_trivial append", "[container]", array_trivial_types)
{
    using value_type = typename TestType::value_type;

    TestType array;

    for (value_type i = 0; i < 150; ++i)
    {
        array.append(i);

        REQUIRE(array.size() == static_cast<size_t>(i + 1));

        for (value_type j = 0; j <= i; ++j)
        {
            CHECK(array[static_cast<size_t>(j)] == j);
        }
    }
}

TEMPLATE_LIST_TEST_CASE("array_trivial remove_at", "[container]", array_trivial_types)
{
    TestType array;
    array.resize(10);
    range::iota(array, 0);

    array.remove_at(5);
    CHECK(array.size() == 9);
    CHECK(array[5] == 6);

    array.remove_at(2);
    CHECK(array.size() == 8);
    CHECK(array[2] == 3);

    array.remove_at(2);
    CHECK(array.size() == 7);
    CHECK(array[2] == 4);
}

TEMPLATE_LIST_TEST_CASE("array_trivial remove_it", "[container]", array_trivial_types)
{
    TestType array;
    array.resize(10);
    range::iota(array, 0);

    array.remove_it(array.begin() + 5);
    CHECK(array.size() == 9);
    CHECK(array[5] == 6);

    array.remove_it(array.begin() + 2);
    CHECK(array.size() == 8);
    CHECK(array[2] == 3);

    array.remove_it(array.begin() + 2);
    CHECK(array.size() == 7);
    CHECK(array[2] == 4);
}

TEMPLATE_LIST_TEST_CASE("array_trivial remove_at_swap_last", "[container]", array_trivial_types)
{
    TestType array;
    array.resize(10);
    range::iota(array, 0);

    array.remove_at_swap_last(5);
    CHECK(array.size() == 9);
    CHECK(array[5] == 9);

    array.remove_at_swap_last(2);
    CHECK(array.size() == 8);
    CHECK(array[2] == 8);

    array.remove_at_swap_last(2);
    CHECK(array.size() == 7);
    CHECK(array[2] == 7);
}

TEMPLATE_LIST_TEST_CASE("array_trivial remove_one", "[container]", array_trivial_types)
{
    TestType array;
    array.resize(10);
    range::iota(array, 0);

    array.remove_one(5);
    CHECK(array.size() == 9);
    CHECK(array[5] == 6);

    array.remove_one(2);
    CHECK(array.size() == 8);
    CHECK(array[2] == 3);

    array.remove_one(2);
    CHECK(array.size() == 8);
    CHECK(array[2] == 3);
}

TEMPLATE_LIST_TEST_CASE("array_trivial remove_one_swap_last", "[container]", array_trivial_types)
{
    TestType array;
    array.resize(10);
    range::iota(array, 0);

    array.remove_one_swap_last(5);
    CHECK(array.size() == 9);
    CHECK(array[5] == 9);

    array.remove_one_swap_last(2);
    CHECK(array.size() == 8);
    CHECK(array[2] == 8);

    array.remove_one_swap_last(3);
    CHECK(array.size() == 7);
    CHECK(array[3] == 7);

    array.remove_one_swap_last(3);
    CHECK(array.size() == 7);
}

TEMPLATE_LIST_TEST_CASE("array_trivial remove_first", "[container]", array_trivial_types)
{
    TestType array;
    array.resize(10);
    range::iota(array, 0);

    array.remove_first();
    CHECK(array.size() == 9);
    CHECK(array[0] == 1);

    array.remove_first();
    CHECK(array.size() == 8);
    CHECK(array[0] == 2);

    array.remove_first();
    CHECK(array.size() == 7);
    CHECK(array[0] == 3);
}

TEMPLATE_LIST_TEST_CASE("array_trivial remove_first_swap_last", "[container]", array_trivial_types)
{
    TestType array;
    array.resize(10);
    range::iota(array, 0);

    array.remove_first_swap_last();
    CHECK(array.size() == 9);
    CHECK(array.first() == 9);

    array.remove_first_swap_last();
    CHECK(array.size() == 8);
    CHECK(array.first() == 8);

    array.remove_first_swap_last();
    CHECK(array.size() == 7);
    CHECK(array.first() == 7);
}

TEMPLATE_LIST_TEST_CASE("array_trivial remove_last", "[container]", array_trivial_types)
{
    TestType array;
    array.resize(10);

    array.remove_last();
    CHECK(array.size() == 9);

    array.remove_last();
    CHECK(array.size() == 8);

    array.remove_last();
    CHECK(array.size() == 7);
}

TEMPLATE_LIST_TEST_CASE("array_trivial resize", "[container]", array_trivial_types)
{
    using value_type = typename TestType::value_type;
    using size_type = typename TestType::size_type;

    TestType array;
    array.resize(32);

    REQUIRE(array.size() == 32);
    range::iota(array, 0);

    array.resize(64);
    for (size_type i = 0; i < 32; ++i)
    {
        CHECK(array[i] == static_cast<value_type>(i));
    }
}

TEMPLATE_LIST_TEST_CASE("array_trivial resize value", "[container]", array_trivial_types)
{
    using size_type = typename TestType::size_type;

    TestType array;
    array.resize(32, 8);

    REQUIRE(array.size() == 32);
    for (size_type i = 0; i < 32; ++i)
    {
        CHECK(array[i] == 8);
    }

    array.resize(64, 12);

    REQUIRE(array.size() == 64);
    for (size_type i = 0; i < 32; ++i)
    {
        CHECK(array[i] == 8);
    }
    for (size_type i = 32; i < 64; ++i)
    {
        CHECK(array[i] == 12);
    }
}

} // namespace nxx::details
