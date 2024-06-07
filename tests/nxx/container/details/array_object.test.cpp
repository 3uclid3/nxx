#include <catch2/catch_template_test_macros.hpp>

#include <tuple>

#include <nxx/container/details/array_object.hpp>
#include <nxx/def.hpp>
#include <nxx/memory/object.mock.hpp>
#include <nxx/utility/as_const.hpp>

namespace nxx::details {

struct array_object_fixture : mock::basic_object_fixture<mock::small_object>,
                              mock::basic_object_fixture<mock::copy_only_small_object>,
                              mock::basic_object_fixture<mock::move_only_small_object>,
                              mock::basic_object_fixture<mock::object>,
                              mock::basic_object_fixture<mock::copy_only_object>,
                              mock::basic_object_fixture<mock::move_only_object>
{
    template<typename ObjectT, typename SizeT>
    void iota_objects(array_object<ObjectT, SizeT>& array, u32_t offset)
    {
        for (size_t i = 0; i < array.size(); ++i)
        {
            array[i].value = offset + static_cast<u32_t>(i);
        }
    }

    template<typename ObjectT, typename SizeT, typename ActionT, typename PostActionCheckT>
    void check_prepend_impl(const ActionT action, PostActionCheckT post_action_check)
    {
        array_object<ObjectT, SizeT> array;
        for (size_t i = 0; i < 150; ++i)
        {
            ObjectT obj(static_cast<u32_t>(i));
            action(array, obj);

            REQUIRE(array.size() == (i + 1));
            post_action_check(array);

            for (size_t j = 0; j <= i; ++j)
            {
                CHECK(array[j].value == static_cast<u32_t>(i - j));
            }
        }
    }

    template<typename ObjectT>
    void check_prepend_copy()
    {
        auto action = [](auto& array, const auto& obj) { array.prepend(obj); };
        auto post_action_check = [](const auto& array) { CHECK(array.first().ctor_copy_called); };

        check_prepend_impl<ObjectT, u32_t>(action, post_action_check);
        check_prepend_impl<ObjectT, u64_t>(action, post_action_check);
    }

    template<typename ObjectT>
    void check_prepend_move()
    {
        auto action = [](auto& array, auto&& obj) { array.prepend(move(obj)); };
        auto post_action_check = [](const auto& array) { CHECK(array.first().ctor_move_called); };

        check_prepend_impl<ObjectT, u32_t>(action, post_action_check);
        check_prepend_impl<ObjectT, u64_t>(action, post_action_check);
    }

    template<typename ObjectT, typename SizeT, typename ActionT, typename PostActionCheckT>
    void check_append_impl(const ActionT action, PostActionCheckT post_action_check)
    {
        array_object<ObjectT, SizeT> array;
        for (size_t i = 0; i < 150; ++i)
        {
            ObjectT obj(static_cast<u32_t>(i));
            action(array, obj);

            REQUIRE(array.size() == i + 1);
            post_action_check(array);

            for (size_t j = 0; j <= i; ++j)
            {
                CHECK(array[j].value == static_cast<u32_t>(j));
            }
        }
    }

    template<typename ObjectT>
    void check_append_copy()
    {
        auto action = [](auto& array, const auto& obj) { array.append(obj); };
        auto post_action_check = [](const auto& array) { CHECK(array.last().ctor_copy_called); };

        check_append_impl<ObjectT, u32_t>(action, post_action_check);
        check_append_impl<ObjectT, u64_t>(action, post_action_check);
    }

    template<typename ObjectT>
    void check_append_move()
    {
        auto action = [](auto& array, auto&& obj) { array.append(move(obj)); };
        auto post_action_check = [](const auto& array) { CHECK(array.last().ctor_move_called); };

        check_append_impl<ObjectT, u32_t>(action, post_action_check);
        check_append_impl<ObjectT, u64_t>(action, post_action_check);
    }

    template<typename ObjectT, typename SizeT>
    void check_emplace_first_impl()
    {
        array_object<ObjectT, SizeT> array;

        for (size_t i = 0; i < 150; ++i)
        {
            array.emplace_first(i);

            REQUIRE(array.size() == i + 1);
            CHECK(array.first().ctor_value_called);

            for (size_t j = 0; j <= i; ++j)
            {
                CHECK(array[j].value == static_cast<u32_t>(i - j));
            }
        }
    }

    template<typename ObjectT>
    void check_emplace_first()
    {
        check_emplace_first_impl<ObjectT, u32_t>();
        check_emplace_first_impl<ObjectT, u64_t>();
    }

    template<typename ObjectT, typename SizeT>
    void check_emplace_last_impl()
    {
        array_object<ObjectT, SizeT> array;

        for (size_t i = 0; i < 150; ++i)
        {
            array.emplace_last(i);

            REQUIRE(array.size() == i + 1);
            CHECK(array[i].ctor_value_called);

            for (size_t j = 0; j <= i; ++j)
            {
                CHECK(array[j].value == j);
            }
        }
    }

    template<typename ObjectT>
    void check_emplace_last()
    {
        check_emplace_last_impl<ObjectT, u32_t>();
        check_emplace_last_impl<ObjectT, u64_t>();
    }

    template<typename ObjectT, typename SizeT>
    void check_remove_at_impl()
    {
        array_object<ObjectT, SizeT> array{10};
        iota_objects(array, 0);

        array.remove_at(5);
        CHECK(array.size() == 9);
        CHECK(array[5].value == 6);

        array.remove_at(2);
        CHECK(array.size() == 8);
        CHECK(array[2].value == 3);

        array.remove_at(2);
        CHECK(array.size() == 7);
        CHECK(array[2].value == 4);
    }

    template<typename ObjectT>
    void check_remove_at()
    {
        check_remove_at_impl<ObjectT, u32_t>();
        check_remove_at_impl<ObjectT, u64_t>();
    }

    template<typename ObjectT, typename SizeT>
    void check_remove_at_swap_last_impl()
    {
        array_object<ObjectT, SizeT> array{10};
        iota_objects(array, 0);

        ObjectT::total_dtor_count = 0;

        array.remove_at_swap_last(5);
        CHECK(ObjectT::total_dtor_count == 2);
        CHECK(array.size() == 9);
        CHECK(array[5].value == 9);

        array.remove_at_swap_last(2);
        CHECK(ObjectT::total_dtor_count == 4);
        CHECK(array.size() == 8);
        CHECK(array[2].value == 8);

        array.remove_at_swap_last(2);
        CHECK(ObjectT::total_dtor_count == 6);
        CHECK(array.size() == 7);
        CHECK(array[2].value == 7);
    }

    template<typename ObjectT>
    void check_remove_at_swap_last()
    {
        check_remove_at_swap_last_impl<ObjectT, u32_t>();
        check_remove_at_swap_last_impl<ObjectT, u64_t>();
    }

    template<typename ObjectT, typename SizeT>
    void check_remove_one_impl()
    {
        array_object<ObjectT, SizeT> array{10};
        iota_objects(array, 0);

        array.remove_one(ObjectT(5));
        CHECK(array.size() == 9);
        CHECK(array[5].value == 6);

        array.remove_one(ObjectT(2));
        CHECK(array.size() == 8);
        CHECK(array[2].value == 3);

        array.remove_one(ObjectT(2));
        CHECK(array.size() == 8);
        CHECK(array[2].value == 3);
    }

    template<typename ObjectT>
    void check_remove_one()
    {
        check_remove_one_impl<ObjectT, u32_t>();
        check_remove_one_impl<ObjectT, u64_t>();
    }

    template<typename ObjectT, typename SizeT>
    void check_remove_one_swap_last_impl()
    {
        array_object<ObjectT, SizeT> array{10};
        iota_objects(array, 0);

        // 3 dtor for tmp in swap
        ObjectT::total_dtor_count = 0;

        array.remove_one_swap_last(ObjectT(5));
        CHECK(ObjectT::total_dtor_count == 3);
        CHECK(array.size() == 9);
        CHECK(array[5].value == 9);

        array.remove_one_swap_last(ObjectT(2));
        CHECK(ObjectT::total_dtor_count == 6);
        CHECK(array.size() == 8);
        CHECK(array[2].value == 8);

        array.remove_one_swap_last(ObjectT(3));
        CHECK(ObjectT::total_dtor_count == 9);
        CHECK(array.size() == 7);
        CHECK(array[3].value == 7);

        array.remove_one_swap_last(ObjectT(3));
        CHECK(ObjectT::total_dtor_count == 10);
        CHECK(array.size() == 7);
    }

    template<typename ObjectT>
    void check_remove_one_swap_last()
    {
        check_remove_one_swap_last_impl<ObjectT, u32_t>();
        check_remove_one_swap_last_impl<ObjectT, u64_t>();
    }

    template<typename ObjectT, typename SizeT>
    void check_remove_first_swap_last_impl()
    {
        array_object<ObjectT, SizeT> array{10};
        iota_objects(array, 0);

        // 2 dtor for tmp in swap
        ObjectT::total_dtor_count = 0;

        array.remove_first_swap_last();
        CHECK(ObjectT::total_dtor_count == 2);
        CHECK(array.size() == 9);
        CHECK(array.first().value == 9);

        array.remove_first_swap_last();
        CHECK(ObjectT::total_dtor_count == 4);
        CHECK(array.size() == 8);
        CHECK(array.first().value == 8);

        array.remove_first_swap_last();
        CHECK(ObjectT::total_dtor_count == 6);
        CHECK(array.size() == 7);
        CHECK(array.first().value == 7);
    }

    template<typename ObjectT>
    void check_remove_first_swap_last()
    {
        check_remove_first_swap_last_impl<ObjectT, u32_t>();
        check_remove_first_swap_last_impl<ObjectT, u64_t>();
    }

    template<typename ObjectT, typename SizeT>
    void check_remove_last_impl()
    {
        array_object<ObjectT, SizeT> array{10};

        ObjectT::total_dtor_count = 0;

        array.remove_last();
        CHECK(ObjectT::total_dtor_count == 1);
        CHECK(array.size() == 9);

        array.remove_last();
        CHECK(ObjectT::total_dtor_count == 2);
        CHECK(array.size() == 8);

        array.remove_last();
        CHECK(ObjectT::total_dtor_count == 3);
        CHECK(array.size() == 7);
    }

    template<typename ObjectT>
    void check_remove_last()
    {
        check_remove_last_impl<ObjectT, u32_t>();
        check_remove_last_impl<ObjectT, u64_t>();
    }
};

TEST_CASE_METHOD(array_object_fixture, "array_object prepend copy", "[container]")
{
    check_prepend_copy<mock::small_object>();
    check_prepend_copy<mock::object>();
    check_prepend_copy<mock::copy_only_small_object>();
    check_prepend_copy<mock::copy_only_object>();
}

TEST_CASE_METHOD(array_object_fixture, "array_object prepend move", "[container]")
{
    check_prepend_move<mock::small_object>();
    check_prepend_move<mock::object>();
    check_prepend_move<mock::move_only_small_object>();
    check_prepend_move<mock::move_only_object>();
}

TEST_CASE_METHOD(array_object_fixture, "array_object append copy", "[container]")
{
    check_append_copy<mock::small_object>();
    check_append_copy<mock::object>();
    check_append_copy<mock::copy_only_small_object>();
    check_append_copy<mock::copy_only_object>();
}

TEST_CASE_METHOD(array_object_fixture, "array_object append move", "[container]")
{
    check_append_move<mock::small_object>();
    check_append_move<mock::object>();
    check_append_move<mock::move_only_small_object>();
    check_append_move<mock::move_only_object>();
}

TEST_CASE_METHOD(array_object_fixture, "array_object emplace_first", "[container]")
{
    check_emplace_first<mock::small_object>();
    check_emplace_first<mock::object>();
    check_emplace_first<mock::copy_only_small_object>();
    check_emplace_first<mock::copy_only_object>();
    check_emplace_first<mock::move_only_small_object>();
    check_emplace_first<mock::move_only_object>();
}

TEST_CASE_METHOD(array_object_fixture, "array_object emplace_last", "[container]")
{
    check_emplace_last<mock::small_object>();
    check_emplace_last<mock::object>();
    check_emplace_last<mock::copy_only_small_object>();
    check_emplace_last<mock::copy_only_object>();
    check_emplace_last<mock::move_only_small_object>();
    check_emplace_last<mock::move_only_object>();
}

TEST_CASE_METHOD(array_object_fixture, "array_object remove_at", "[container]")
{
    check_remove_at<mock::small_object>();
    check_remove_at<mock::object>();
    check_remove_at<mock::copy_only_small_object>();
    check_remove_at<mock::copy_only_object>();
    check_remove_at<mock::move_only_small_object>();
    check_remove_at<mock::move_only_object>();
}

TEST_CASE_METHOD(array_object_fixture, "array_object remove_at_swap_last", "[container]")
{
    check_remove_at_swap_last<mock::small_object>();
    check_remove_at_swap_last<mock::object>();
    check_remove_at_swap_last<mock::copy_only_small_object>();
    check_remove_at_swap_last<mock::copy_only_object>();
    check_remove_at_swap_last<mock::move_only_small_object>();
    check_remove_at_swap_last<mock::move_only_object>();
}

TEST_CASE_METHOD(array_object_fixture, "array_object remove_one", "[container]")
{
    check_remove_one<mock::small_object>();
    check_remove_one<mock::object>();
    check_remove_one<mock::copy_only_small_object>();
    check_remove_one<mock::copy_only_object>();
    check_remove_one<mock::move_only_small_object>();
    check_remove_one<mock::move_only_object>();
}

TEST_CASE_METHOD(array_object_fixture, "array_object remove_one_swap_last", "[container]")
{
    check_remove_one_swap_last<mock::small_object>();
    check_remove_one_swap_last<mock::object>();
    check_remove_one_swap_last<mock::copy_only_small_object>();
    check_remove_one_swap_last<mock::copy_only_object>();
    check_remove_one_swap_last<mock::move_only_small_object>();
    check_remove_one_swap_last<mock::move_only_object>();
}

TEST_CASE_METHOD(array_object_fixture, "array_object remove_first_swap_last", "[container]")
{
    check_remove_first_swap_last<mock::small_object>();
    check_remove_first_swap_last<mock::object>();
    check_remove_first_swap_last<mock::copy_only_small_object>();
    check_remove_first_swap_last<mock::copy_only_object>();
    check_remove_first_swap_last<mock::move_only_small_object>();
    check_remove_first_swap_last<mock::move_only_object>();
}

TEST_CASE_METHOD(array_object_fixture, "array_object remove_last", "[container]")
{
    check_remove_last<mock::small_object>();
    check_remove_last<mock::object>();
    check_remove_last<mock::copy_only_small_object>();
    check_remove_last<mock::copy_only_object>();
    check_remove_last<mock::move_only_small_object>();
    check_remove_last<mock::move_only_object>();
}

} // namespace nxx::details