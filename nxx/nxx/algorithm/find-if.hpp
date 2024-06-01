#pragma once

#include <nxx/algorithm/iterator.hpp>

namespace nxx {

template<typename IteratorT, typename PredicateT>
constexpr auto find_if(IteratorT begin, IteratorT end, PredicateT predicate)
{
    for (auto it = begin; it != end; ++it)
    {
        if (predicate(*it))
        {
            return it;
        }
    }

    return end;
}

namespace range {

template<typename RangeT, typename PredicateT>
constexpr auto find_if(RangeT& range, PredicateT predicate)
{
    return nxx::find_if(range::begin(range), range::end(range), predicate);
}

} // namespace range

} // namespace nxx