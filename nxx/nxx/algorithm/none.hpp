#pragma once

#include <nxx/algorithm/iterator.hpp>

namespace nxx {

template<typename IteratorT, typename ValueT>
constexpr bool none(IteratorT begin, IteratorT end, const ValueT& value)
{
    for (auto it = begin; it != end; ++it)
    {
        if (*it == value)
        {
            return false;
        }
    }

    return true;
}

namespace range {

template<typename RangeT, typename ValueT>
constexpr bool none(RangeT& range, const ValueT& value)
{
    return nxx::none(range::begin(range), range::end(range), value);
}

} // namespace range

} // namespace nxx
