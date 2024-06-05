#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/utility/swap.hpp>

namespace nxx {

struct moveable
{
    constexpr moveable() = default;
    constexpr moveable(const moveable&) = delete;
    constexpr moveable& operator=(const moveable&) = delete;

    constexpr moveable(size_t v)
        : value(v)
    {
    }

    constexpr moveable(moveable&& other)
    {
        value = other.value;
        ++move_count;
    }

    constexpr moveable& operator=(moveable&& other)
    {
        value = other.value;
        ++move_count;
        return *this;
    }

    size_t value{0};
    size_t move_count{0};
};

TEST_CASE("swap")
{
    moveable lhs{42};
    moveable rhs{69};

    swap(lhs, rhs);

    CHECK(lhs.move_count == 1);
    CHECK(lhs.value == 69);

    CHECK(rhs.move_count == 1);
    CHECK(rhs.value == 42);
}

} // namespace nxx
