#pragma once

#include <nxx/def.hpp>
#include <nxx/type_trait/is_integral.hpp>

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

#if __has_builtin(__make_integer_seq)
template<typename T, T SizeT>
using make_integer_sequence = __make_integer_seq<integer_sequence, T, SizeT>;
#elif __has_builtin(__integer_pack)
template<typename T, T SizeT>
using make_integer_sequence = integer_sequence<T, __integer_pack(SizeT)...>;
#endif

template<size_t SizeT>
using make_index_sequence = make_integer_sequence<size_t, SizeT>;

template<typename... Ts>
using index_sequence_for = make_index_sequence<sizeof...(Ts)>;

} // namespace nxx
