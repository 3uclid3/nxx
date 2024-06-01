#pragma once

#include <nxx/memory/address_of.hpp>
#include <nxx/memory/new.hpp>
#include <nxx/type_trait/is_static_array.hpp>
#include <nxx/utility/forward.hpp>

namespace nxx {

template<typename T, typename... ArgsT>
constexpr T* construct_at(T* ptr, ArgsT&&... args)
{
    return ::new (static_cast<void*>(ptr)) T(forward<ArgsT>(args)...);
}

template<typename T>
constexpr void destroy_at(T* ptr)
{
    if constexpr (is_static_array<T>)
    {
        for (auto& elem : *ptr)
        {
            destroy_at(address_of(elem));
        }
    }
    else
    {
        ptr->~T();
    }
}

} // namespace nxx