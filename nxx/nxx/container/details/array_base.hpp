#pragma once

#include <nxx/container/details/array_data.hpp>
#include <nxx/debug/assert.hpp>
// #include <nxx/iterator/reverse-iterator.hpp>
#include <nxx/memory/memory_block.hpp>
#include <nxx/memory/voidify.hpp>

namespace nxx::details {

template<typename T, typename SizeT>
class array_base : public array_data<SizeT>
{
    using super = array_data<SizeT>;

public:
    using size_type = SizeT;
    using value_type = T;

    using const_pointer = const T*;
    using pointer = T*;

    using const_reference = const T&;
    using reference = T&;

    using const_iterator = const T*;
    using iterator = T*;

    // using const_reverse_iterator = nxx::reverse_iterator<const_iterator>;
    // using      reverse_iterator = nxx::reverse_iterator<iterator>;

public:
    using super::capacity;
    using super::is_empty;
    using super::size;

public:
    constexpr const_reference operator[](size_t index) const;
    constexpr reference operator[](size_t index);

public:
    constexpr const_reference first() const;
    constexpr reference first();

    constexpr const_reference last() const;
    constexpr reference last();

    constexpr const_pointer data() const;
    constexpr pointer data();

public:
    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;

    constexpr const_iterator cbegin() const;
    constexpr const_iterator cend() const;

    constexpr iterator begin();
    constexpr iterator end();

    //constexpr ConstReverseIterator rbegin() const;
    //constexpr ConstReverseIterator rend() const;
    //constexpr ConstReverseIterator rcbegin() const;
    //constexpr ConstReverseIterator rcend() const;

    // constexpr reverse_iterator rbegin();
    // constexpr reverse_iterator rend();

protected:
    // Helper to figure out the offset of the first element
    constexpr uintptr_t get_offset_of_first_inplace() const;
    constexpr void* get_address_of_first_inplace() const;

    constexpr bool is_inplace_buffer() const;

    constexpr bool is_valid_iterator(const_iterator it) const;
};

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::const_reference array_base<T, SizeT>::operator[](size_t index) const
{
    NXX_ASSERT(index < size());

    return data()[index];
}

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::reference array_base<T, SizeT>::operator[](size_t index)
{
    NXX_ASSERT(index < size());

    return data()[index];
}

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::const_reference array_base<T, SizeT>::first() const
{
    return (*this)[0];
}

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::reference array_base<T, SizeT>::first()
{
    return (*this)[0];
}

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::const_reference array_base<T, SizeT>::last() const
{
    NXX_ASSERT(!is_empty());
    return (*this)[size() - 1];
}

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::reference array_base<T, SizeT>::last()
{
    NXX_ASSERT(!is_empty());
    return (*this)[size() - 1];
}

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::const_pointer array_base<T, SizeT>::data() const
{
    return reinterpret_cast<const_pointer>(super::_buffer);
}

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::pointer array_base<T, SizeT>::data()
{
    return reinterpret_cast<pointer>(super::_buffer);
}

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::const_iterator array_base<T, SizeT>::begin() const
{
    return const_iterator{data()};
}

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::const_iterator array_base<T, SizeT>::end() const
{
    return const_iterator{data() + size()};
}

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::const_iterator array_base<T, SizeT>::cbegin() const
{
    return begin();
}

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::const_iterator array_base<T, SizeT>::cend() const
{
    return end();
}

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::iterator array_base<T, SizeT>::begin()
{
    return iterator{data()};
}

template<typename T, typename SizeT>
constexpr array_base<T, SizeT>::iterator array_base<T, SizeT>::end()
{
    return iterator{data() + size()};
}

template<typename T, typename SizeT>
constexpr uintptr_t array_base<T, SizeT>::get_offset_of_first_inplace() const
{
    struct internal_array
    {
        alignas(super) u8_t base[sizeof(super)];
        alignas(T) u8_t first[sizeof(T)];
    };

    return offsetof(internal_array, first);
}

template<typename T, typename SizeT>
constexpr void* array_base<T, SizeT>::get_address_of_first_inplace() const
{
    /// Find the address of the first element. For this pointer math to be valid
    /// with inplace of 0 for T with lots of alignment, it's important that
    /// array_data is properly-aligned even for inplace of 0.
    return const_cast<void*>(reinterpret_cast<const void*>(reinterpret_cast<const u8_t*>(this) + get_offset_of_first_inplace()));
}

template<typename T, typename SizeT>
constexpr bool array_base<T, SizeT>::is_inplace_buffer() const
{
    return super::_buffer == get_address_of_first_inplace();
}

template<typename T, typename SizeT>
constexpr bool array_base<T, SizeT>::is_valid_iterator(const_iterator it) const
{
    const u8_t* buffer = static_cast<const u8_t*>(super::_buffer);
    const u8_t* buffer_end = buffer + sizeof(T) * size();

    const void* void_ptr = it;
    const u8_t* pointer = static_cast<const u8_t*>(void_ptr);

    return pointer >= buffer && pointer < buffer_end;
}

} // namespace nxx::details