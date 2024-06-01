#pragma once

#include <nxx/def.hpp>
#include <nxx/type_trait/is_const.hpp>
#include <nxx/type_trait/remove_const_volatile.hpp>
#include <nxx/utility/integer_sequence.hpp>
#include <nxx/utility/move.hpp>

namespace nxx {

template<typename T, size_t SizeT>
class static_array;

template<typename T, size_t SizeT>
constexpr static_array<remove_const_volatile<T>, SizeT> to_static_array(T (&array)[SizeT]);

template<typename T, size_t SizeT>
constexpr static_array<remove_const_volatile<T>, SizeT> to_static_array(T (&&array)[SizeT]);

template<typename T, size_t SizeT>
class static_array
{
public:
    using value_type = T;

    using reference = T&;
    using const_reference = const T&;

    using iterator = T*;
    using const_iterator = const T*;

    using pointer = T*;
    using const_pointer = const T*;

    using size_type = size_t;
    using difference_type = ptrdiff_t;

public:
    void fill(const T& value);
    void swap(static_array& other);

public:
    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;

    constexpr const_iterator cbegin() const;
    constexpr const_iterator cend() const;

    constexpr iterator begin();
    constexpr iterator end();

public:
    constexpr size_type size() const;

    constexpr size_type max_size() const;
    constexpr bool is_empty() const;

public:
    constexpr const_reference operator[](size_type index) const;
    constexpr reference operator[](size_type index);

    constexpr const_reference first() const;
    constexpr reference first();

    constexpr const_reference last() const;
    constexpr reference last();

    constexpr const value_type* data() const;
    constexpr value_type* data();

public:
    T _data[SizeT];
};

template<typename T>
class static_array<T, 0>
{
public:
    using value_type = T;

    using reference = T&;
    using const_reference = const T&;

    using iterator = T*;
    using const_iterator = const T*;

    using pointer = T*;
    using const_pointer = const T*;

    using size_type = size_t;
    using difference_type = ptrdiff_t;

public:
    void fill(const T& value);
    void swap(static_array& other);

public:
    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;

    constexpr const_iterator cbegin() const;
    constexpr const_iterator cend() const;

    constexpr iterator begin();
    constexpr iterator end();

public:
    constexpr size_type size() const;

    constexpr size_type max_size() const;
    constexpr bool is_empty() const;

public:
    constexpr const_reference operator[](size_type index) const;
    constexpr reference operator[](size_type index);

    constexpr const_reference first() const;
    constexpr reference first();

    constexpr const_reference last() const;
    constexpr reference last();

    constexpr const value_type* data() const;
    constexpr value_type* data();
};

namespace details {

template<typename T, size_t SizeT, size_t... IndexT>
constexpr static_array<remove_const_volatile<T>, SizeT> to_static_array_lvalue(T (&array)[SizeT], index_sequence<IndexT...>)
{
    return {{array[IndexT]...}};
}

template<typename T, size_t SizeT, size_t... IndexT>
constexpr static_array<remove_const_volatile<T>, SizeT> to_static_array_rvalue(T (&&array)[SizeT], index_sequence<IndexT...>)
{
    return {{move(array[IndexT])...}};
}

} // namespace details

template<typename T, size_t SizeT>
constexpr static_array<remove_const_volatile<T>, SizeT> to_static_array(T (&array)[SizeT])
{
    return details::to_static_array_lvalue(array, make_index_sequence<SizeT>());
}

template<typename T, size_t SizeT>
constexpr static_array<remove_const_volatile<T>, SizeT> to_static_array(T (&&array)[SizeT])
{
    return details::to_static_array_rvalue(move(array), make_index_sequence<SizeT>());
}

template<typename T, size_t SizeT>
void static_array<T, SizeT>::fill(const T& value)
{
    for (T& v : *this)
    {
        v = value;
    }
}

template<typename T, size_t SizeT>
void static_array<T, SizeT>::swap(static_array& other)
{
    NXX_ASSERT(false, "To be implemented");
    NXX_UNUSED(other);
}

template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::iterator static_array<T, SizeT>::begin()
{
    return iterator(data());
}

template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::const_iterator static_array<T, SizeT>::begin() const
{
    return const_iterator(data());
}

template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::iterator static_array<T, SizeT>::end()
{
    return iterator(data() + SizeT);
}
template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::const_iterator static_array<T, SizeT>::end() const
{
    return const_iterator(data() + SizeT);
}
template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::const_iterator static_array<T, SizeT>::cbegin() const
{
    return begin();
}
template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::const_iterator static_array<T, SizeT>::cend() const
{
    return end();
}

template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::size_type static_array<T, SizeT>::size() const
{
    return SizeT;
}

template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::size_type static_array<T, SizeT>::max_size() const
{
    return SizeT;
}

template<typename T, size_t SizeT>
constexpr bool static_array<T, SizeT>::is_empty() const
{
    return false;
}

template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::reference static_array<T, SizeT>::operator[](size_type index)
{
    NXX_ASSERT(index < SizeT, "out-of-bounds access in static_array<T, N>");
    return _data[index];
}

template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::const_reference static_array<T, SizeT>::operator[](size_type index) const
{
    NXX_ASSERT(index < SizeT, "out-of-bounds access in static_array<T, N>");
    return _data[index];
}

template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::const_reference static_array<T, SizeT>::first() const
{
    return (*this)[0];
}

template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::reference static_array<T, SizeT>::first()
{
    return (*this)[0];
}

template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::const_reference static_array<T, SizeT>::last() const
{
    return (*this)[SizeT - 1];
}

template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::reference static_array<T, SizeT>::last()
{
    return (*this)[SizeT - 1];
}

template<typename T, size_t SizeT>
constexpr const static_array<T, SizeT>::value_type* static_array<T, SizeT>::data() const
{
    return _data;
}

template<typename T, size_t SizeT>
constexpr static_array<T, SizeT>::value_type* static_array<T, SizeT>::data()
{
    return _data;
}

template<typename T>
void static_array<T, 0>::fill(const T& value)
{
    NXX_UNUSED(value);
}

template<typename T>
void static_array<T, 0>::swap(static_array& other)
{
    NXX_UNUSED(other);
}

template<typename T>
constexpr static_array<T, 0>::iterator static_array<T, 0>::begin()
{
    return iterator(data());
}

template<typename T>
constexpr static_array<T, 0>::const_iterator static_array<T, 0>::begin() const
{
    return const_iterator(data());
}

template<typename T>
constexpr static_array<T, 0>::iterator static_array<T, 0>::end()
{
    return iterator(data());
}

template<typename T>
constexpr static_array<T, 0>::const_iterator static_array<T, 0>::end() const
{
    return const_iterator(data());
}

template<typename T>
constexpr static_array<T, 0>::const_iterator static_array<T, 0>::cbegin() const
{
    return begin();
}

template<typename T>
constexpr static_array<T, 0>::const_iterator static_array<T, 0>::cend() const
{
    return end();
}

template<typename T>
constexpr static_array<T, 0>::size_type static_array<T, 0>::size() const
{
    return 0;
}

template<typename T>
constexpr static_array<T, 0>::size_type static_array<T, 0>::max_size() const
{
    return 0;
}

template<typename T>
constexpr bool static_array<T, 0>::is_empty() const
{
    return true;
}

template<typename T>
constexpr static_array<T, 0>::reference static_array<T, 0>::operator[](size_type index)
{
    NXX_ASSERT(false, "cannot call static_array<T, 0>:::operator[] on a zero-sized static_array");
    NXX_UNUSED(index);
    NXX_UNREACHABLE();
}

template<typename T>
constexpr static_array<T, 0>::const_reference static_array<T, 0>::operator[](size_type index) const
{
    NXX_ASSERT(false, "cannot call static_array<T, 0>:::operator[] on a zero-sized static_array");
    NXX_UNUSED(index);
    NXX_UNREACHABLE();
}

template<typename T>
constexpr static_array<T, 0>::const_reference static_array<T, 0>::first() const
{
    NXX_ASSERT(false, "cannot call static_array<T, 0>::first() on a zero-sized static_array");
    NXX_UNREACHABLE();
}

template<typename T>
constexpr static_array<T, 0>::reference static_array<T, 0>::first()
{
    NXX_ASSERT(false, "cannot call static_array<T, 0>::first() on a zero-sized static_array");
    NXX_UNREACHABLE();
}

template<typename T>
constexpr static_array<T, 0>::const_reference static_array<T, 0>::last() const
{
    NXX_ASSERT(false, "cannot call static_array<T, 0>::data() on a zero-sized static_array");
    NXX_UNREACHABLE();
}

template<typename T>
constexpr static_array<T, 0>::reference static_array<T, 0>::last()
{
    NXX_ASSERT(false, "cannot call static_array<T, 0>::data() on a zero-sized static_array");
    NXX_UNREACHABLE();
}

template<typename T>
constexpr const static_array<T, 0>::value_type* static_array<T, 0>::data() const
{
    return nullptr;
}

template<typename T>
constexpr static_array<T, 0>::value_type* static_array<T, 0>::data()
{
    return nullptr;
}

} // namespace nxx