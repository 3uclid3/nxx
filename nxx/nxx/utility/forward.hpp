#pragma once

#include <nxx/type_trait/is_reference.hpp>
#include <nxx/type_trait/remove_reference.hpp>

namespace nxx {

template<class T>
[[nodiscard]] constexpr T&& forward(remove_reference<T>& v)
{
    return static_cast<T&&>(v);
}

template<class T>
[[nodiscard]] constexpr T&& forward(remove_reference<T>&& v)
{
    static_assert(!is_lvalue_reference<T>, "cannot forward an rvalue as an lvalue");
    return static_cast<T&&>(v);
}

} // namespace nxx
