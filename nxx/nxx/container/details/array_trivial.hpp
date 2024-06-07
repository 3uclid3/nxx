#pragma once

#include <nxx/container/details/array_base.hpp>
#include <nxx/container/details/array_param_type.hpp>
#include <nxx/def.hpp>
#include <nxx/memory/allocate.hpp>
#include <nxx/memory/memory_block.hpp>
#include <nxx/memory/utility.hpp>
#include <nxx/utility/swap.hpp>

namespace nxx::details {

// base class for trivial T's
template<typename T, typename SizeT>
class array_trivial : public array_base<T, SizeT>
{
    using super = array_base<T, SizeT>;
    using typename super::data_size_type;

public:
    using typename super::size_type;
    using typename super::value_type;
    using value_param_type = array_param_type<T>;

    using typename super::const_pointer;
    using typename super::pointer;

    using typename super::const_reference;
    using typename super::reference;

    using typename super::const_iterator;
    using typename super::iterator;

public:
    constexpr array_trivial() = default;
    constexpr array_trivial(size_t initial_size);
    constexpr ~array_trivial();

public:
    using super::capacity;
    using super::is_empty;
    using super::size;

    using super::first;
    using super::last;

    using super::begin;
    using super::end;

    using super::cbegin;
    using super::cend;

public:
    constexpr reference emplace_first(value_param_type value);
    constexpr reference emplace_last(value_param_type value);

    constexpr void prepend(value_param_type value);
    constexpr void append(value_param_type value);

    constexpr void remove_at(size_t index);
    constexpr void remove_at_swap_last(size_t index);

    constexpr void remove_it(const_iterator it);
    constexpr void remove_it_swap_last(const_iterator it);

    constexpr void remove_one(value_param_type value);
    constexpr void remove_one_swap_last(value_param_type value);

    constexpr void remove_first();
    constexpr void remove_first_swap_last();

    constexpr void remove_last();

    constexpr size_t index_of(value_param_type value) const;
    constexpr size_t index_of(const_iterator it) const;

    constexpr void reserve(size_t size);
    constexpr void resize(size_t size);
    constexpr void resize(size_t size, value_param_type value);
    constexpr void clear();
    constexpr void free();

protected:
    constexpr void grow(size_t size, size_t offset = 0);
};

template<typename T, typename SizeT>
constexpr array_trivial<T, SizeT>::array_trivial(size_t initial_size)
{
    grow(initial_size);

    super::_size = static_cast<data_size_type>(initial_size);
}

template<typename T, typename SizeT>
constexpr array_trivial<T, SizeT>::~array_trivial()
{
    free();
}

template<typename T, typename SizeT>
constexpr array_trivial<T, SizeT>::reference array_trivial<T, SizeT>::emplace_first(value_param_type value)
{
    prepend(value);
    return first();
}

template<typename T, typename SizeT>
constexpr array_trivial<T, SizeT>::reference array_trivial<T, SizeT>::emplace_last(value_param_type value)
{
    append(value);
    return last();
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::prepend(value_param_type value)
{
    grow(size() + 1, 1);

    memcpy(super::_buffer, &value, sizeof(T));

    ++super::_size;
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::append(value_param_type value)
{
    grow(size() + 1);

    memcpy(static_cast<u8_t*>(super::_buffer) + super::_size * sizeof(T), &value, sizeof(T));

    ++super::_size;
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::remove_at(size_t index)
{
    NXX_ASSERT(index < size());

    const size_t size_to_move = (size() - index - 1) * sizeof(T);

    memmove(static_cast<u8_t*>(super::_buffer) + index * sizeof(T),
            static_cast<u8_t*>(super::_buffer) + (index + 1) * sizeof(T),
            size_to_move);

    --super::_size;
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::remove_at_swap_last(size_t index)
{
    NXX_ASSERT(index < size());
    swap((*this)[index], last());
    remove_last();
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::remove_it(const_iterator it)
{
    return remove_at(index_of(it));
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::remove_it_swap_last(const_iterator it)
{
    return remove_at_swap_last(index_of(it));
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::remove_one(value_param_type value)
{
    const size_t index = index_of(value);

    if (index < size())
    {
        remove_at(index);
    }
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::remove_one_swap_last(value_param_type value)
{
    const size_t index = index_of(value);

    if (index < size())
    {
        remove_at_swap_last(index);
    }
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::remove_first()
{
    remove_at(0);
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::remove_first_swap_last()
{
    if (size() > 1)
    {
        swap(first(), last());
    }

    remove_last();
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::remove_last()
{
    NXX_ASSERT(!is_empty());

    --super::_size;
}

template<typename T, typename SizeT>
constexpr size_t array_trivial<T, SizeT>::index_of(value_param_type value) const
{
    for (size_t i = 0; i < super::_size; ++i)
    {
        if ((*this)[i] == value)
        {
            return i;
        }
    }
    return super::_size;
}

template<typename T, typename SizeT>
constexpr size_t array_trivial<T, SizeT>::index_of(const_iterator it) const
{
    NXX_ASSERT(super::is_valid_iterator(it));
    return size() - static_cast<size_t>(end() - it);
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::reserve(size_t size)
{
    grow(size);
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::resize(size_t size)
{
    grow(size);

    super::_size = static_cast<data_size_type>(size);
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::resize(size_t size, value_param_type value)
{
    const size_t previous_size = super::_size;

    resize(size);

    for (size_t i = previous_size; i < size; ++i)
    {
        (*this)[i] = value;
    }
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::clear()
{
    super::_size = 0;
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::free()
{
    clear();

    memory_block block(super::_buffer, capacity() * sizeof(T));
    deallocate(block);

    super::_buffer = nullptr;
    super::_capacity = 0;
}

template<typename T, typename SizeT>
constexpr void array_trivial<T, SizeT>::grow(size_t min_capacity, size_t offset)
{
    if (min_capacity <= capacity())
    {
        if (offset > 0)
        {
            memmove(static_cast<u8_t*>(super::_buffer) + offset * sizeof(T),
                    super::_buffer,
                    super::_size * sizeof(T));
        }
        return;
    }

    memory_block new_block = allocate(super::get_next_capacity(min_capacity) * sizeof(T));
    memory_block old_block = memory_block(super::_buffer, super::_capacity * sizeof(T));

    NXX_ASSERT(new_block);

    if (old_block)
    {
        // copy existing data
        memcpy(static_cast<u8_t*>(new_block.ptr) + offset * sizeof(T), old_block.ptr, new_block.size - (offset * sizeof(T)));

        if (!super::is_inplace_buffer())
        {
            deallocate(old_block);
        }
    }

    super::_buffer = new_block.ptr;
    super::_capacity = static_cast<data_size_type>(new_block.size / sizeof(T));
}

} // namespace nxx::details
