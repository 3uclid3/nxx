#include <nxx/utility/ref-wrap.hpp>

#include <catch2/catch_test_macros.hpp>

#include <nxx/def.hpp>
#include <nxx/utility/move.hpp>

namespace nxx {

TEST_CASE("ref_wrap", "[utility]")
{
    int value = 3;

    SECTION("ref")
    {
        ref_wrap<int> rw = ref(value);

        CHECK(rw.get() == value);
    }

    SECTION("ref from ref")
    {
        ref_wrap<int> rw = ref(ref(value));

        CHECK(rw.get() == value);
    }

    SECTION("cref")
    {
        ref_wrap<const int> rw = cref(value);

        CHECK(rw.get() == value);
    }

    SECTION("cref from ref")
    {
        ref_wrap<const int> rw = cref(ref(value));

        CHECK(rw.get() == value);
    }

    SECTION("cref from cref")
    {
        ref_wrap<const int> rw = cref(cref(value));

        CHECK(rw.get() == value);
    }

    SECTION("moveable")
    {
        ref_wrap<int> a = ref(value);
        ref_wrap<int> b = move(a);

        CHECK(b.get() == value);
    }
}

} // namespace nxx