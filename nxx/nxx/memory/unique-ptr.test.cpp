#include <nxx/memory/unique-ptr.hpp>

#include <catch2/catch_test_macros.hpp>

namespace nxx {

TEST_CASE("unique_ptr object delete on exit scope", "[memory]")
{
    static bool dtor_called = false;

    struct dtor_object
    {
        ~dtor_object() { dtor_called = true; }
    };

    {
        unique_ptr<dtor_object> ptr{new dtor_object()};
    }

    CHECK(dtor_called);
}

TEST_CASE("unique_ptr::release will release ownership of the object", "[memory]")
{
    unique_ptr<u32_t> ptr{new u32_t()};

    u32_t* val = ptr.release();

    CHECK_FALSE(ptr);

    delete val;
}

} // namespace NOS