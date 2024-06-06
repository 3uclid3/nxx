#pragma once

#include <nxx/algorithm/iterator.hpp>
#include <nxx/concept/integral.hpp>

namespace nxx {

template<typename IteratorT, integral ValueT>
constexpr void iota(IteratorT begin, IteratorT end, ValueT value)
{
    for (auto it = begin; it != end; ++it, ++value)
    {
        *it = value;
    }
}

namespace range {

template<typename RangeT, integral ValueT>
constexpr void iota(RangeT& range, ValueT value)
{
    nxx::iota(range::begin(range), range::end(range), value);
}

} // namespace range

} // namespace nxx