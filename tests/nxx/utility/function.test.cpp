#include <nxx/utility/function.hpp>

#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>

namespace nxx {

namespace {

static bool free_called{false};

void free()
{
    free_called = true;
}

struct object
{
    void member()
    {
        called = true;
    }

    void cmember() const
    {
        called = true;
    }

    void member_with_argument(int argument)
    {
        called = true;
        called_argument = argument;
    }

    void cmember_with_argument(int argument) const
    {
        called = true;
        called_argument = argument;
    }

    static void static_member()
    {
        static_called = true;
    }

    static void static_member_with_argument(int argument)
    {
        static_called = true;
        static_called_argument = argument;
    }

    mutable bool called{false};
    mutable int called_argument{0};

    inline static bool static_called{false};
    inline static int static_called_argument{0};
};

} // namespace

TEST_CASE("function is empty", "[utility]")
{
    function<void()> function;

    CHECK_FALSE(function);
}

TEST_CASE("function is a free function", "[utility]")
{
    function<void()> function{&free};

    function();

    CHECK(free_called);
}

TEST_CASE("function is a lambda", "[function]")
{
    function<void()> function;

    SECTION("without capture")
    {
        static bool called = false;

        function = []() { called = true; };
        function();

        CHECK(called);
    }

    SECTION("with capture")
    {
        bool called = false;

        function = [&called]() { called = true; };
        function();

        CHECK(called);
    }
}

} // namespace nxx