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
            CHECK(bitmap.is_set(offset + i) == expected);
        }
    };

    void check_are_clear(size_t offset, size_t size, bool expected = true)
    {
        for (size_t i = 0; i < size; ++i)
        {
            CHECK(bitmap.is_clear(offset + i) == expected);
        }
    };

    bitmap<static_array<u8_t, 4>> bitmap{to_static_array<u8_t>({0xFF, 0x00, 0xFF, 0x00})};
};

TEST_CASE("bitmap size", "[container]")
{
    SECTION("0")
    {
        bitmap<static_array<u8_t, 0>> bitmap;

        CHECK(bitmap.size() == 0);
    }

    SECTION("2")
    {
        bitmap<static_array<u8_t, 2>> bitmap;

        CHECK(bitmap.size() == 16);
    }

    SECTION("4")
    {
        bitmap<static_array<u8_t, 4>> bitmap;

        CHECK(bitmap.size() == 32);
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
    bitmap.set(8);
    bitmap.set(10);
    bitmap.set(12);

    CHECK(bitmap.is_set(8));
    CHECK(bitmap.is_clear(9));
    CHECK(bitmap.is_set(10));
    CHECK(bitmap.is_clear(11));
    CHECK(bitmap.is_set(12));
    CHECK(bitmap.is_clear(13));
    CHECK(bitmap.is_clear(14));
    CHECK(bitmap.is_clear(15));

    check_are_set(0, 8, true);
    check_are_set(16, 8, true);
    check_are_set(24, 8, false);
}

TEST_CASE_METHOD(bitmap_fixture, "bitmap clear", "[container]")
{
    bitmap.clear(0);
    bitmap.clear(3);
    bitmap.clear(4);

    CHECK(bitmap.is_clear(0));
    CHECK(bitmap.is_set(1));
    CHECK(bitmap.is_set(2));
    CHECK(bitmap.is_clear(3));
    CHECK(bitmap.is_clear(4));
    CHECK(bitmap.is_set(5));
    CHECK(bitmap.is_set(6));
    CHECK(bitmap.is_set(7));

    check_are_clear(8, 8, true);
    check_are_clear(16, 8, false);
    check_are_clear(24, 8, true);
}

TEST_CASE_METHOD(bitmap_fixture, "bitmap reset", "[container]")
{
    SECTION("reset to 0")
    {
        bitmap.reset(0);

        check_are_clear(0, bitmap.size());
    }

    SECTION("reset to 0xFF")
    {
        bitmap.reset(0xFF);

        check_are_set(0, bitmap.size());
    }
}

} // namespace nxx
