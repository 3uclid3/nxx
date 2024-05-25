#include <catch2/catch_test_macros.hpp>

#include <nxx/container/static-array.hpp>
#include <nxx/string/format-to.hpp>
#include <nxx/string/string-view.hpp>

namespace nxx {

struct output
{
    void write(char c)
    {
        REQUIRE(_buffer_size < _buffer.size());

        _buffer[_buffer_size++] = c;
    }

    string_view view() const
    {
        return {_buffer.data(), _buffer_size};
    }

    // TODO use an Array
    static_array<char, 256> _buffer;
    size_t _buffer_size{0};
};

TEST_CASE("format_to - bool", "[String]")
{
    output out;

    format_to(out, "Format a bool '{}'", true);

    string_view sv = out.view();

    CHECK(sv == "Format a bool 'true'");
}

TEST_CASE("format_to - char", "[String]")
{
    output out;

    format_to(out, "Format a char '{}'", 'c');

    string_view sv = out.view();

    CHECK(sv == "Format a char 'c'");
}

TEST_CASE("format_to - s8_t", "[String]")
{
    output out;

    format_to(out, "Format a s8 '{}'", s8_t{-42});

    string_view sv = out.view();

    CHECK(sv == "Format a s8 '-42'");
}

TEST_CASE("format_to - u8_t", "[String]")
{
    output out;

    format_to(out, "Format a u8 '{}'", u8_t{42});

    string_view sv = out.view();

    CHECK(sv == "Format a u8 '42'");
}

TEST_CASE("format_to - s16_t", "[String]")
{
    output out;

    format_to(out, "Format a s16 '{}'", s16_t{-42});

    string_view sv = out.view();

    CHECK(sv == "Format a s16 '-42'");
}

TEST_CASE("format_to - u16_t", "[String]")
{
    output out;

    format_to(out, "Format a u16 '{}'", u16_t{42});

    string_view sv = out.view();

    CHECK(sv == "Format a u16 '42'");
}

TEST_CASE("format_to - s32_t", "[String]")
{
    output out;

    format_to(out, "Format a s32_t '{}'", s32_t{-42});

    string_view sv = out.view();

    CHECK(sv == "Format a s32_t '-42'");
}

TEST_CASE("format_to - u32_t", "[String]")
{
    output out;

    format_to(out, "Format a u32 '{}'", u32_t{42});

    string_view sv = out.view();

    CHECK(sv == "Format a u32 '42'");
}

TEST_CASE("format_to - s64_t", "[String]")
{
    output out;

    format_to(out, "Format a s64 '{}'", s64_t{-42});

    string_view sv = out.view();

    CHECK(sv == "Format a s64 '-42'");
}

TEST_CASE("format_to - u64_t", "[String]")
{
    output out;

    format_to(out, "Format a u64 '{}'", u64_t{42});

    string_view sv = out.view();

    CHECK(sv == "Format a u64 '42'");
}

TEST_CASE("format_to - String", "[String]")
{
    output out;

    format_to(out, "Format a string '{}'", "A String");

    string_view sv = out.view();

    CHECK(sv == "Format a string 'A String'");
}

TEST_CASE("format_to - binary presentation", "[String]")
{
    output out;

    SECTION("LowerCase")
    {
        format_to(out, "Format to binary '{:b}'", 0b101010);

        string_view sv = out.view();

        CHECK(sv == "Format to binary '101010'");
    }

    SECTION("UpperCase")
    {
        format_to(out, "Format to binary '{:B}'", 0B101010);

        string_view sv = out.view();

        CHECK(sv == "Format to binary '101010'");
    }
}

TEST_CASE("format_to - hex presentation", "[String]")
{
    output out;

    SECTION("LowerCase")
    {
        format_to(out, "Format to hex '{:x}'", 0xfefefefe);

        string_view sv = out.view();

        CHECK(sv == "Format to hex 'fefefefe'");
    }

    SECTION("UpperCase")
    {
        format_to(out, "Format to hex '{:X}'", 0xFEFEFEFE);

        string_view sv = out.view();

        CHECK(sv == "Format to hex 'FEFEFEFE'");
    }
}

TEST_CASE("format_to - position", "[String]")
{
    output out;

    format_to(out, "Format at 1: {1}; at 2 {2}; at 0 {0}", 42, 22, 24);

    string_view sv = out.view();

    CHECK(sv == "Format at 1: 22; at 2 24; at 0 42");
}

TEST_CASE("format_to - finishing with {:PRESENTATION}", "[String]")
{
    output out;

    format_to(out, "0x{:x}", 0xfefefefe);

    string_view sv = out.view();

    CHECK(sv == "0xfefefefe");
}

} // namespace NOS