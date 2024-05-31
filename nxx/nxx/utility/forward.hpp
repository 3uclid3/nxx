#pragma once

#include <nxx/type-trait/is-lvalue-reference.hpp>
#include <nxx/type-trait/remove-reference.hpp>

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
