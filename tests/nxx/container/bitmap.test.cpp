#include <catch2/catch_test_macros.hpp>

#include <nxx/container/bitmap.hpp>
#include <nxx/container/static_array.hpp>

namespace nxx {

struct bitmap_fixture
{
    void check_are_set(size_t offset, size_t size, bool expected = true)
    {
        for (size_t i = 0; i < size; ++i)
        {
            CHECK(bm.is_set(offset + i) == expected);
        }
    };

    void check_are_clear(size_t offset, size_t size, bool expected = true)
    {
        for (size_t i = 0; i < size; ++i)
        {
            CHECK(bm.is_clear(offset + i) == expected);
        }
    };

    bitmap<static_array<u8_t, 4>> bm{to_static_array<u8_t>({0xFF, 0x00, 0xFF, 0x00})};
};

TEST_CASE("bitmap size", "[container]")
{
    SECTION("0")
    {
        bitmap<static_array<u8_t, 0>> bm;

        CHECK(bm.size() == 0);
    }

    SECTION("2")
    {
        bitmap<static_array<u8_t, 2>> bm;

        CHECK(bm.size() == 16);
    }

    SECTION("4")
    {
        bitmap<static_array<u8_t, 4>> bm;

        CHECK(bm.size() == 32);
    }
}

TEST_CASE_METHOD(bitmap_fixture, "bitmap is_set", "[container]")
{
    check_are_set(0, 8, true);
    check_are_set(8, 8, false);
    check_are_set(16, 8, true);
    check_are_set(24, 8, false);
}

TEST_CASE_METHOD(bitmap_fixture, "bitmap is_clear", "[container]")
{
    check_are_clear(0, 8, false);
    check_are_clear(8, 8, true);
    check_are_clear(16, 8, false);
    check_are_clear(24, 8, true);
}

TEST_CASE_METHOD(bitmap_fixture, "bitmap set", "[container]")
{
    bm.set(8);
    bm.set(10);
    bm.set(12);

    CHECK(bm.is_set(8));
    CHECK(bm.is_clear(9));
    CHECK(bm.is_set(10));
    CHECK(bm.is_clear(11));
    CHECK(bm.is_set(12));
    CHECK(bm.is_clear(13));
    CHECK(bm.is_clear(14));
    CHECK(bm.is_clear(15));

    check_are_set(0, 8, true);
    check_are_set(16, 8, true);
    check_are_set(24, 8, false);
}

TEST_CASE_METHOD(bitmap_fixture, "bitmap clear", "[container]")
{
    bm.clear(0);
    bm.clear(3);
    bm.clear(4);

    CHECK(bm.is_clear(0));
    CHECK(bm.is_set(1));
    CHECK(bm.is_set(2));
    CHECK(bm.is_clear(3));
    CHECK(bm.is_clear(4));
    CHECK(bm.is_set(5));
    CHECK(bm.is_set(6));
    CHECK(bm.is_set(7));

    check_are_clear(8, 8, true);
    check_are_clear(16, 8, false);
    check_are_clear(24, 8, true);
}

TEST_CASE_METHOD(bitmap_fixture, "bitmap reset", "[container]")
{
    SECTION("reset to 0")
    {
        bm.reset(0);

        check_are_clear(0, bm.size());
    }

    SECTION("reset to 0xFF")
    {
        bm.reset(0xFF);

        check_are_set(0, bm.size());
    }
}

} // namespace nxx
