#pragma once

#include <nxx/memory/address_of.hpp>

namespace nxx {

template<typename T>
constexpr void* voidify(T& v)
{
    return address_of(v);
}

} // namespace nxx
