#pragma once

#include <nxx/concept/integral.hpp>
#include <nxx/container/static_array.hpp>
#include <nxx/def.hpp>

namespace nxx {

struct assert_memory_corruption_reporter
{
    template<integral T>
    static void report(const void* corrupted_ptr, T expected, T actual)
    {
        NXX_ASSERT(expected == actual);
        NXX_UNUSED(corrupted_ptr);
        NXX_UNUSED(expected);
        NXX_UNUSED(actual);
    }
};

template<integral T, T PatternT, size_t SizeT = 32, typename ReporterT = assert_memory_corruption_reporter>
struct memory_corruption_detector
{
    static constexpr T pattern = PatternT;

    constexpr memory_corruption_detector();
    constexpr ~memory_corruption_detector();

    static_array<T, SizeT> guard;
};

template<integral T, T PatternT, size_t SizeT, typename ReporterT>
constexpr memory_corruption_detector<T, PatternT, SizeT, ReporterT>::memory_corruption_detector()
{
    guard.fill(pattern);
}

template<integral T, T PatternT, size_t SizeT, typename ReporterT>
constexpr memory_corruption_detector<T, PatternT, SizeT, ReporterT>::~memory_corruption_detector()
{
    for (const T& value : guard)
    {
        if (value != pattern)
        {
            ReporterT::report(&value, pattern, value);
        }
    }
}

} // namespace nxx
