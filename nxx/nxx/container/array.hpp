#pragma once

#include <nxx/container/details/array_base_type.hpp>
#include <nxx/container/details/array_size_type.hpp>
#include <nxx/def.hpp>

namespace nxx {

template<typename T, typename SizeT = details::array_size_type<T>>
class array : public details::array_base_type<T, SizeT>
{
    using super = typename details::array_base_type<T, SizeT>;

public:
    using typename super::value_type;

    using typename super::const_pointer;
    using typename super::pointer;

    using typename super::const_reference;
    using typename super::reference;

    using typename super::const_iterator;
    using typename super::iterator;

public:
    constexpr array() = default;
    constexpr array(size_t initial_size);
    constexpr array(size_t initial_size, const T& initial_value);
};

template<typename T, typename TSize>
constexpr array<T, TSize>::array(size_t initial_size)
    : super(initial_size)
{
}

template<typename T, typename TSize>
constexpr array<T, TSize>::array(size_t initial_size, const T& initial_value)
    : super(initial_size)
{
    for (T& v : *this)
    {
        v = initial_value;
    }
}

} // namespace nxx