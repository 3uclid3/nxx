#pragma once

#include <nxx/algorithm/iterator.hpp>

namespace nxx {

template<typename IteratorT, typename PredicateT>
constexpr bool any_of(IteratorT begin, IteratorT end, PredicateT predicate)
{
    for (auto it = begin; it != end; ++it)
    {
        if (predicate(*it))
        {
            return true;
        }
    }

    return false;
}

namespace range {

template<typename RangeT, typename PredicateT>
constexpr bool any_of(RangeT& range, PredicateT predicate)
{
    return nxx::any_of(range::begin(range), range::end(range), predicate);
}

} // namespace range

} // namespace nxx
