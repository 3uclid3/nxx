#pragma once

#include <nxx/def.hpp>
#include <nxx/type-trait/is-integral.hpp>

#if !__has_builtin(__make_integer_seq)
#error "__make_integer_seq must be implemented"
#endif
namespace nxx {

template<typename T, T... ValuesT>
struct integer_sequence
{
    using value_type = T;

    static_assert(is_integral<T>, "integer_sequence can only be instantiated with an integral type");
    static constexpr size_t size() { return sizeof...(ValuesT); }
};

template<size_t... ValuesT>
using index_sequence = integer_sequence<size_t, ValuesT...>;

template<typename T, T SizeT>
using make_integer_sequence = __make_integer_seq<integer_sequence, T, SizeT>;

template<size_t SizeT>
using make_index_sequence = make_integer_sequence<size_t, SizeT>;

template<typename... Ts>
using index_sequence_for = make_index_sequence<sizeof...(Ts)>;

} // namespace nxx
