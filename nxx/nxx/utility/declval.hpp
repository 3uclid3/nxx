#pragma once

#include <nxx/type_trait/is_same.hpp>

namespace nxx::impl {

template<class T>
T&& declval(int);

template<class T>
T declval(long);

} // namespace nxx::impl

namespace nxx {

template<class T>
decltype(impl::declval<T>(0)) declval()
{
    static_assert(!is_same<T, T>,
                  "declval can only be used in an unevaluated context. "
                  "It's likely that your current usage is trying to extract a value from the function.");
}

} // namespace nxx
