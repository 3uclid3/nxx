#include <catch2/catch_test_macros.hpp>

#include <nxx/string/utility.hpp>

namespace nxx {

constexpr const char* src = "hello";
constexpr size_t len = strlen(src);

TEST_CASE("strlen", "[string]")
{
    CHECK(strlen(src) == len);
    STATIC_CHECK(strlen(src) == len);
}

TEST_CASE("strcpy", "[string]")
{
    char dest[len];
    strcpy(dest, src);

    CHECK(strcmp(dest, src) == 0);
}

TEST_CASE("strncpy", "[string]")
{
    char dest[10];
    strncpy(dest, src, 10);

    CHECK(strcmp(dest, src) == 0);
}

TEST_CASE("strcmp", "[string]")
{
    CHECK(strcmp("hello", "hello") == 0);
    CHECK(strcmp("hello", "hellp") < 0);
    CHECK(strcmp("hellp", "hello") > 0);
    
    STATIC_CHECK(strcmp("hello", "hello") == 0);
    STATIC_CHECK(strcmp("hello", "hellp") < 0);
    STATIC_CHECK(strcmp("hellp", "hello") > 0);
}

TEST_CASE("strncmp", "[string]")
{
    CHECK(strncmp("hello0", "hello1", 5) == 0);
    CHECK(strncmp("hello0", "hellp1", 5) < 0);
    CHECK(strncmp("hellp0", "hello1", 5) > 0);
    
    STATIC_CHECK(strncmp("hello0", "hello1", 5) == 0);
    STATIC_CHECK(strncmp("hello0", "hellp1", 5) < 0);
    STATIC_CHECK(strncmp("hellp0", "hello1", 5) > 0);
}

} // namespace nxx
