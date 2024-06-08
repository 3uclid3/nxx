#pragma once

#include <nxx/type_trait/integral_constant.hpp>
#include <nxx/type_trait/is_same.hpp>

namespace nxx::impl {

struct is_referenceable_tester
{
    template<typename T>
    static T& test(int);

    template<typename T>
    static false_type test(...);
};

template<typename T>
struct is_referenceable : is_not_same<decltype(is_referenceable_tester::test<T>(0)), false_type>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_referenceable = impl::is_referenceable<T>::value;

} // namespace nxx
