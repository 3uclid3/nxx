#pragma once

#include <nxx/algorithm/iterator.hpp>

namespace nxx {

template<typename IteratorT, typename ValueT>
constexpr auto find(IteratorT begin, IteratorT end, const ValueT& value)
{
    for (auto it = begin; it != end; ++it)
    {
        if (*it == value)
        {
            return it;
        }
    }

    return end;
}

namespace range {

template<typename RangeT, typename ValueT>
constexpr auto find(RangeT& range, const ValueT& value)
{
    return nxx::find(range::begin(range), range::end(range), value);
}

} // namespace range

} // namespace nxx