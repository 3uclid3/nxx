#include <catch2/catch_test_macros.hpp>

#include <nxx/container/span.hpp>
#include <nxx/container/static-array.hpp>
#include <nxx/string/to-string-view.hpp>

namespace nxx {

TEST_CASE("to_string_view", "[string]")
{
    static_array<char, 64> raw_buffer;
    span<char> buffer{raw_buffer.data(), raw_buffer.size()};

    SECTION("Binary")
    {
        SECTION("u8")
        {
            auto result = to_string_view(u8_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("s8")
        {
            auto result = to_string_view(s8_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("u16")
        {
            auto result = to_string_view(u16_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("s16")
        {
            auto result = to_string_view(s16_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("u32")
        {
            auto result = to_string_view(u32_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("s32")
        {
            auto result = to_string_view(s32_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("u64")
        {
            auto result = to_string_view(u64_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }

        SECTION("s64")
        {
            auto result = to_string_view(s64_t{0b01010}, buffer, 2);
            CHECK(result == "1010");
        }
    }

    SECTION("Decimal")
    {
        SECTION("u8")
        {
            auto result = to_string_view(u8_t{42}, buffer, 10);
            CHECK(result == "42");
        }

        SECTION("s8")
        {
            auto result = to_string_view(s8_t{-42}, buffer, 10);
            CHECK(result == "-42");
        }

        SECTION("u16")
        {
            auto result = to_string_view(u16_t{42}, buffer, 10);
            CHECK(result == "42");
        }

        SECTION("s16")
        {
            auto result = to_string_view(s16_t{-42}, buffer, 10);
            CHECK(result == "-42");
        }

        SECTION("u32")
        {
            auto result = to_string_view(u32_t{42}, buffer, 10);
            CHECK(result == "42");
        }

        SECTION("s32")
        {
            auto result = to_string_view(s32_t{-42}, buffer, 10);
            CHECK(result == "-42");
        }

        SECTION("u64")
        {
            auto result = to_string_view(u64_t{42}, buffer, 10);
            CHECK(result == "42");
        }

        SECTION("s64")
        {
            auto result = to_string_view(s64_t{-42}, buffer, 10);
            CHECK(result == "-42");
        }
    }

    SECTION("Hexadecimal")
    {
        SECTION("LowerCase")
        {
            SECTION("u8")
            {
                auto result = to_string_view(u8_t{0xfe}, buffer, 16);
                CHECK(result == "fe");
            }

            SECTION("s8")
            {
                auto result = to_string_view(s8_t{0x2e}, buffer, 16);
                CHECK(result == "2e");
            }

            SECTION("u16")
            {
                auto result = to_string_view(u16_t{0xfefe}, buffer, 16);
                CHECK(result == "fefe");
            }

            SECTION("s16")
            {
                auto result = to_string_view(s16_t{0x2e2e}, buffer, 16);
                CHECK(result == "2e2e");
            }

            SECTION("u32")
            {
                auto result = to_string_view(u32_t{0xfefefefe}, buffer, 16);
                CHECK(result == "fefefefe");
            }

            SECTION("s32")
            {
                auto result = to_string_view(s32_t{0x2e2e2e2e}, buffer, 16);
                CHECK(result == "2e2e2e2e");
            }

            SECTION("u64")
            {
                auto result = to_string_view(u64_t{0xfefefefefefefefe}, buffer, 16);
                CHECK(result == "fefefefefefefefe");
            }

            SECTION("s64")
            {
                auto result = to_string_view(s64_t{0x2e2e2e2e2e2e2e2e}, buffer, 16);
                CHECK(result == "2e2e2e2e2e2e2e2e");
            }
        }

        SECTION("UpperCase")
        {
            SECTION("u8")
            {
                auto result = to_string_view(u8_t{0xFE}, buffer, 16, true);
                CHECK(result == "FE");
            }

            SECTION("s8")
            {
                auto result = to_string_view(s8_t{0x2E}, buffer, 16, true);
                CHECK(result == "2E");
            }

            SECTION("u16")
            {
                auto result = to_string_view(u16_t{0xFEFE}, buffer, 16, true);
                CHECK(result == "FEFE");
            }

            SECTION("s16")
            {
                auto result = to_string_view(s16_t{0x2E2E}, buffer, 16, true);
                CHECK(result == "2E2E");
            }

            SECTION("u32")
            {
                auto result = to_string_view(u32_t{0xFEFEFEFE}, buffer, 16, true);
                CHECK(result == "FEFEFEFE");
            }

            SECTION("s32")
            {
                auto result = to_string_view(s32_t{0x2E2E2E2E}, buffer, 16, true);
                CHECK(result == "2E2E2E2E");
            }

            SECTION("u64")
            {
                auto result = to_string_view(u64_t{0xFEFEFEFEFEFEFEFE}, buffer, 16, true);
                CHECK(result == "FEFEFEFEFEFEFEFE");
            }

            SECTION("s64")
            {
                auto result = to_string_view(s64_t{0x2E2E2E2E2E2E2E2E}, buffer, 16, true);
                CHECK(result == "2E2E2E2E2E2E2E2E");
            }
        }
    }
}

} // namespace NOS