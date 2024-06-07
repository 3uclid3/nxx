#include <catch2/catch_test_macros.hpp>

#include <nxx/container/details/array_base.hpp>
#include <nxx/memory/address_of.hpp>
#include <nxx/memory/allocator/null_allocator.hpp>
#include <nxx/memory/allocator/stack_allocator.hpp>

namespace nxx::details {

namespace {
template<typename T, typename SizeT>
class inplace_array_base : public array_base<T, SizeT>
{
    using super = array_base<T, SizeT>;

public:
    static constexpr size_t inplace_size = sizeof(T) * 10;

    constexpr inplace_array_base() { set_buffer(address_of(inplace)); }

    constexpr void set_buffer(void* buffer) { super::_buffer = buffer; }

    using super::get_address_of_first_inplace;
    using super::is_inplace_buffer;

    alignas(T) u8_t inplace[inplace_size];
};
} // namespace

TEST_CASE("details::array_base", "[Array]")
{
    int buffer[10];

    SECTION("SizeT = u32_t")
    {
        inplace_array_base<int, u32_t> array;

        CHECK(array.get_address_of_first_inplace() == address_of(array.inplace));
        CHECK(array.is_inplace_buffer());

        // simulate allocation
        array.set_buffer(address_of(buffer));

        CHECK(array.get_address_of_first_inplace() != address_of(buffer));
        CHECK_FALSE(array.is_inplace_buffer());
    }

    SECTION("SizeT = u64_t")
    {
        inplace_array_base<int, u64_t> array;

        CHECK(array.get_address_of_first_inplace() == address_of(array.inplace));
        CHECK(array.is_inplace_buffer());

        // simulate allocation
        array.set_buffer(address_of(buffer));

        CHECK(array.get_address_of_first_inplace() != address_of(buffer));
        CHECK_FALSE(array.is_inplace_buffer());
    }
}

} // namespace nxx::details