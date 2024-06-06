#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/memory/allocator/allocator_traits.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx::allocator_traits {

struct empty_allocator
{
};

class non_empty_allocator
{
public:
    [[nodiscard]] constexpr memory_block allocate(size_t) { return nullblk; }
    [[nodiscard]] constexpr bool owns(const memory_block&) const { return false; }
    constexpr bool expand(memory_block&, size_t) { return false; }
    constexpr bool reallocate(memory_block&, size_t) { return false; }
    constexpr void deallocate(memory_block&) {}
    constexpr void deallocate_all() {}
};

TEST_CASE("allocator_trait", "[memory][type-trait]")
{
    STATIC_CHECK(has_owns<non_empty_allocator>);
    STATIC_CHECK(has_expand<non_empty_allocator>);
    STATIC_CHECK(has_deallocate_all<non_empty_allocator>);

    STATIC_CHECK_FALSE(has_owns<empty_allocator>);
    STATIC_CHECK_FALSE(has_expand<empty_allocator>);
    STATIC_CHECK_FALSE(has_deallocate_all<empty_allocator>);
}

} // namespace nxx::allocator