#pragma once

#include <nxx/algorithm/iterator.hpp>

namespace nxx {

template<typename IteratorT, typename ValueT>
constexpr bool any(IteratorT begin, IteratorT end, const ValueT& value)
{
    for (auto it = begin; it != end; ++it)
    {
        if (*it == value)
        {
            return true;
        }
    }

    return false;
}

namespace range {

template<typename RangeT, typename ValueT>
constexpr bool any(RangeT& range, const ValueT& value)
{
    return nxx::any(range::begin(range), range::end(range), value);
}

} // namespace range

} // namespace nxx
