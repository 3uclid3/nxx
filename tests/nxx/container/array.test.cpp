#include <catch2/catch_test_macros.hpp>

#include <nxx/container/array.hpp>
#include <nxx/memory/object.mock.hpp>

namespace nxx {

TEST_CASE("array capacity", "[container]")
{
    SECTION("default ctor")
    {
        array<int> a;
        CHECK(a.capacity() == 0);
    }

    SECTION("ctor with initial size")
    {
        array<int> a(100);
        CHECK(a.capacity() == 100);

        a.append(0);

        CHECK(a.capacity() > 101);
    }
}

TEST_CASE("array is_empty", "[container]")
{
    array<int> a;
    CHECK(a.is_empty());

    a.append(0);
    CHECK_FALSE(a.is_empty());

    a.clear();
    CHECK(a.is_empty());
}

TEST_CASE("array reserve", "[container]")
{
    SECTION("allocate at least size")
    {
        array<int> a;
        a.reserve(10);

        CHECK(a.is_empty());
        CHECK(a.capacity() >= 10);
    }

    SECTION("does nothing if capacity is equal or higher than requested size")
    {
        array<int> a;
        a.reserve(100);
        CHECK(a.is_empty());
        CHECK(a.capacity() == 100);

        a.reserve(50);
        CHECK(a.is_empty());
        CHECK(a.capacity() == 100);

        a.reserve(100);
        CHECK(a.is_empty());
        CHECK(a.capacity() == 100);
    }

    SECTION("allocate a new buffer capacity is lower than requested size")
    {
        array<int> a;
        a.reserve(100);
        CHECK(a.is_empty());
        CHECK(a.capacity() == 100);

        a.reserve(150);
        CHECK(a.is_empty());
        CHECK(a.capacity() >= 150);
    }

    SECTION("content is moved to new buffer")
    {
        array<int> a(100);
        CHECK(a.size() == 100);
        CHECK(a.capacity() == 100);

        a.reserve(150);
        CHECK(a.size() == 100);
        CHECK(a.capacity() >= 150);
    }
}

TEST_CASE("array resize(size)", "[container]")
{
    SECTION("copyable/moveable")
    {
        array<mock::object> a(100);
        a.resize(50);
        CHECK(a.size() == 50);
        CHECK(a.capacity() == 100);

        a.resize(200);
        CHECK(a.size() == 200);
        CHECK(a.capacity() >= 200);
    }

    SECTION("moveable only")
    {
        array<mock::move_only_object> a(100);
        a.resize(50);
        CHECK(a.size() == 50);
        CHECK(a.capacity() == 100);

        a.resize(200);
        CHECK(a.size() == 200);
        CHECK(a.capacity() >= 200);
    }
}

TEST_CASE("array resize(size, value)", "[container]")
{
    array<int> a;

    a.resize(50, 1);
    CHECK(a.size() == 50);
    CHECK(a.capacity() == 50);

    a.resize(25, 2);
    CHECK(a.size() == 25);
    CHECK(a.capacity() == 50);

    a.resize(75, 3);
    CHECK(a.size() == 75);
    CHECK(a.capacity() >= 75);

    for (size_t i = 0; i < 25; ++i)
    {
        CHECK(a[i] == 1);
    }

    for (size_t i = 25; i < 75; ++i)
    {
        CHECK(a[i] == 3);
    }
}

TEST_CASE("array size", "[container]")
{
    array<int> a;

    CHECK(a.size() == 0);
    a.append(0);

    CHECK(a.size() == 1);
    a.append(1);

    CHECK(a.size() == 2);
    a.append(2);

    CHECK(a.size() == 3);

    a.remove_last();
    CHECK(a.size() == 2);

    a.remove_last();
    CHECK(a.size() == 1);

    a.remove_last();
    CHECK(a.size() == 0);
}

TEST_CASE("array data", "[container]")
{
    struct fail
    {
        // clang-format off
        constexpr fail() = default;
        constexpr fail(int i) : v(i) {}
        constexpr ~fail() {}
        fail* operator&() const { FAIL(); return nullptr; }
        int v{};
        // clang-format on
    };

    SECTION("non-const")
    {
        SECTION("empty")
        {
            array<int> a;
            CHECK(a.data() == nullptr);
        }

        SECTION("non-empty")
        {
            array<int> a(100);
            CHECK(a.data() == address_of(a.first()));
        }

        SECTION("dereference")
        {
            array<fail> a(100);
            CHECK(a.data() == address_of(a.first()));
        }
    }

    SECTION("const")
    {
        SECTION("empty")
        {
            const array<int> a{};
            CHECK(a.data() == nullptr);
        }

        SECTION("non-empty")
        {
            const array<int> a(100);
            CHECK(a.data() == address_of(a.first()));
        }

        SECTION("dereference")
        {
            const array<fail> a(100);
            CHECK(a.data() == address_of(a.first()));
        }
    }
}

} // namespace nxx
