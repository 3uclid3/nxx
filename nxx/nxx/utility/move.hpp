#pragma once

#include <nxx/type_trait/remove_reference.hpp>

namespace nxx {

template<typename T>
constexpr remove_reference<T>&& move(T&& v)
{
    return static_cast<remove_reference<T>&&>(v);
}

} // namespace nxx
