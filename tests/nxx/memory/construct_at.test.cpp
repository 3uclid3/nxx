#include <nxx/memory/construct_at.hpp>

#include <catch2/catch_test_macros.hpp>

#include <nxx/memory/object.mock.hpp>

namespace nxx {

TEST_CASE_METHOD(mock::object_fixture, "construct_at then destroy_at", "[memory]")
{
    static_array<u8_t, sizeof(mock::object)> buffer;

    mock::object* obj = construct_at(static_cast<mock::object*>(static_cast<void*>(buffer.data())));

    REQUIRE(mock::object::ctor_count == 1);

    CHECK(obj->ctor_default);

    destroy_at(obj);

    CHECK(mock::object::dtor_count == 1);
}

} // namespace nxx
