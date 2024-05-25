#pragma once

#include <nxx/type-trait/is-function.hpp>

namespace nxx {

template<class T>
struct pointer_traits
{
    using pointer = T;
};

template<typename PtrT>
constexpr auto to_address(const PtrT& ptr);

template<typename T>
constexpr T* to_address(T* ptr);

template<typename PtrT>
constexpr auto to_address(const PtrT& ptr)
{
    if constexpr (requires { pointer_traits<PtrT>::to_address(ptr); })
    {
        return pointer_traits<PtrT>::to_address(ptr);
    }

    return to_address(ptr.operator->());
}

template<typename T>
constexpr T* to_address(T* ptr)
{
    static_assert(!is_function<T>);
    return ptr;
}

} // namespace nxx
