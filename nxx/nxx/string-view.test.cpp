#include <catch2/catch_test_macros.hpp>

#include <nxx/string-view.hpp>

namespace nxx {

TEST_CASE("string_view - ctor")
{
    constexpr const char* my_cstr = "my_cstr";
    constexpr size_t my_cstr_size = sizeof(my_cstr) - 1ULL;

    SECTION("str, size")
    {
        const string_view str_view{my_cstr, my_cstr_size};

        CHECK(str_view.data() == my_cstr);
        CHECK(str_view.size() == my_cstr_size);
    }

    SECTION("cstr")
    {
        const string_view str_view{my_cstr};

        CHECK(str_view.size() == my_cstr_size);
    }
}

TEST_CASE("string_view::operator==")
{
    CHECK(string_view{"lorem ipsum"} == string_view{"lorem ipsum"});
    CHECK(string_view{"lorem"} == string_view{"lorem"});
    CHECK(string_view{"ipsum"} == string_view{"ipsum"});

    CHECK_FALSE(string_view{"lorem ipsum"} == string_view{"ipsum lorem"});
    CHECK_FALSE(string_view{"lorem"} == string_view{"ipsum"});
    CHECK_FALSE(string_view{"ipsum"} == string_view{"lorem"});

    CHECK(string_view{"lorem ipsum"} == "lorem ipsum");
    CHECK(string_view{"lorem"} == "lorem");
    CHECK(string_view{"ipsum"} == "ipsum");

    CHECK_FALSE(string_view{"lorem ipsum"} == "ipsum lorem");
    CHECK_FALSE(string_view{"lorem"} == "ipsum");
    CHECK_FALSE(string_view{"ipsum"} == "lorem");
}

TEST_CASE("string_view::find_last_of")
{
    constexpr string_view lorem_ipsum_str{"lorem ipsum"};
    constexpr string_view empty_str{""};

    CHECK(lorem_ipsum_str.find_last_of('l') == 0);
    CHECK(lorem_ipsum_str.find_last_of(' ') == 5);
    CHECK(lorem_ipsum_str.find_last_of('m') == lorem_ipsum_str.size() - 1);
    
    CHECK(lorem_ipsum_str.find_last_of('z') == string_view::npos);
    CHECK(empty_str.find_last_of('z') == string_view::npos);
}

TEST_CASE("string_view::substr")
{
    constexpr string_view lorem_ipsum_str{"lorem ipsum"};
    constexpr string_view empty_str{""};

    CHECK(lorem_ipsum_str.substr(0, 5) == "lorem");
    CHECK(lorem_ipsum_str.substr(6) == "ipsum");

    CHECK(empty_str.substr(0, 5) == string_view());
    CHECK(empty_str.substr(6) == string_view());
}

} // namespace nxx