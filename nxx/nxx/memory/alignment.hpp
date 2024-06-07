#pragma once

#include <nxx/concept/integral.hpp>
#include <nxx/def.hpp>
#include <nxx/type_trait/make_unsigned.hpp>

namespace nxx {

inline static constexpr size_t default_alignment{8};

constexpr size_t round_to_alignment(size_t size, size_t align)
{
    return size + ((size % align) == 0 ? 0 : align - (size % align));
}

constexpr auto align_down(integral auto n, integral auto a)
{
    constexpr auto align_down_impl = [](auto un, auto ua) {
        return (un & ~(ua - 1));
    };
    return align_down_impl(make_unsigned<decltype(n)>(n), make_unsigned<decltype(a)>(a));
}

constexpr auto align_up(integral auto n, integral auto a)
{
    return align_down(n + a - 1, a);
}

} // namespace nxx
