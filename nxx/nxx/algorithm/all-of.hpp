#pragma once

#include <nxx/algorithm/iterator.hpp>

namespace nxx {

template<typename IteratorT, typename PredicateT>
constexpr bool all_of(IteratorT begin, IteratorT end, PredicateT predicate)
{
    for (auto it = begin; it != end; ++it)
    {
        if (!predicate(*it))
        {
            return false;
        }
    }

    return true;
}

namespace range {

template<typename RangeT, typename ValueT>
constexpr bool all_of(RangeT& range, const ValueT& value)
{
    return nxx::all_of(range::begin(range), range::end(range), value);
}

} // namespace range

} // namespace nxx
