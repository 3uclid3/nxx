#pragma once

#include <nxx/type-trait/add-const.hpp>

namespace nxx {

template<class T>
constexpr add_const<T>& as_const(T& v)
{
    return v;
}

template<class T>
void as_const(const T&&) = delete;

} // namespace nxx
