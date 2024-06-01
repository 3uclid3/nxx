#pragma once

#include <nxx/type_trait/is_move_assignable.hpp>
#include <nxx/type_trait/is_move_constructible.hpp>
#include <nxx/utility/move.hpp>

namespace nxx {

template<typename T>
requires(is_move_assignable<T> && is_move_constructible<T>)
constexpr void swap(T& lhs, T& rhs)
{
    T tmp(move(lhs));
    lhs = move(rhs);
    rhs = move(tmp);
}

} // namespace nxx
