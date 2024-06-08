#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/type_trait/integral_constant.hpp>
#include <nxx/type_trait/is_same.hpp>

namespace nxx {

template<typename T, T ValueT>
void check()
{
    using ic_t = integral_constant<T, ValueT>;

    STATIC_CHECK(is_same<typename ic_t::value_type, T>);
    STATIC_CHECK(ic_t::value == ValueT);

    constexpr const ic_t ic;

    STATIC_CHECK(static_cast<T>(ic) == ValueT);
    STATIC_CHECK(ic() == ValueT);
}

TEST_CASE("integral_constant", "[type_trait]")
{
    check<u8_t, 0>();
    check<u8_t, 128>();

    check<u32_t, 0>();
    check<u32_t, 2048>();
}

} // namespace nxx