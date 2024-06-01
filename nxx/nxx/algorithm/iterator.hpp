#pragma once

namespace nxx {

template<typename I>
auto begin(I& i)
{
    return i.begin();
}

template<typename I>
auto end(I& i)
{
    return i.end();
}

template<typename I>
auto cbegin(const I& i)
{
    return i.cbegin();
}

template<typename I>
auto cend(const I& i)
{
    return i.cend();
}

namespace range {

template<typename R>
auto begin(R& range)
{
    return range.begin();
}

template<typename R>
auto end(R& range)
{
    return range.end();
}

template<typename R>
auto cbegin(const R& range)
{
    return range.cbegin();
}

template<typename R>
auto cend(const R& range)
{
    return range.cend();
}

} // namespace range
} // namespace nxx
