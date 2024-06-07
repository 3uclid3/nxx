#pragma once

#include <nxx/container/details/array_base.hpp>
#include <nxx/memory/allocate.hpp>
#include <nxx/memory/construct_at.hpp>
#include <nxx/memory/memory_block.hpp>
#include <nxx/type_trait/is_copy_assignable.hpp>
#include <nxx/type_trait/is_copy_constructible.hpp>
#include <nxx/type_trait/is_move_assignable.hpp>
#include <nxx/type_trait/is_move_constructible.hpp>
#include <nxx/utility/forward.hpp>
#include <nxx/utility/move.hpp>
#include <nxx/utility/swap.hpp>

namespace nxx::details {

// super class for non-trivial T's
template<typename T, typename SizeT>
class array_object : public array_base<T, SizeT>
{
    using super = array_base<T, SizeT>;
    using typename super::data_size_type;

public:
    using typename super::size_type;
    using typename super::value_type;

    using typename super::const_pointer;
    using typename super::pointer;

    using typename super::const_reference;
    using typename super::reference;

public:
    constexpr array_object() = default;
    constexpr array_object(size_t initial_size);
    constexpr ~array_object();

public:
    using super::capacity;
    using super::is_empty;
    using super::size;

    using super::first;
    using super::last;

public:
    constexpr void prepend(const_reference value);
    constexpr void prepend(T&& value);

    constexpr void append(const_reference value);
    constexpr void append(T&& value);

    template<typename... TArgs>
    constexpr reference emplace_first(TArgs&&... args);

    template<typename... TArgs>
    constexpr reference emplace_last(TArgs&&... args);

    constexpr void remove_at(size_t index);
    constexpr void remove_at_swap_last(size_t index);

    constexpr void remove_one(const_reference value);
    constexpr void remove_one_swap_last(const_reference value);

    constexpr void remove_first();
    constexpr void remove_first_swap_last();

    constexpr void remove_last();

    constexpr size_t index_of(const_reference value) const;

    constexpr void reserve(size_t size);
    constexpr void resize(size_t size);
    constexpr void clear();
    constexpr void free();

protected:
    static void construct(T* to, T* from);
    static void take(T* to, T* from);
    static void destroy_range(T* begin, T* end);

    constexpr void grow(size_t min_capacity, size_t offset = 0);
};

template<typename T, typename SizeT>
constexpr array_object<T, SizeT>::array_object(size_t initial_size)
{
    resize(initial_size);
}

template<typename T, typename SizeT>
constexpr array_object<T, SizeT>::~array_object()
{
    clear();

    memory_block block(super::_buffer, super::_capacity * sizeof(T));
    deallocate(block);
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::prepend(const_reference value)
{
    grow(super::size() + 1, 1);

    construct_at(static_cast<T*>(super::_buffer), value);

    ++super::_size;
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::prepend(T&& value)
{
    grow(super::size() + 1, 1);

    construct_at(static_cast<T*>(super::_buffer), move(value));

    ++super::_size;
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::append(const_reference value)
{
    grow(super::size() + 1);

    construct_at(static_cast<T*>(super::_buffer) + super::_size, value);

    ++super::_size;
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::append(T&& value)
{
    grow(super::size() + 1);

    construct_at(static_cast<T*>(super::_buffer) + super::_size, move(value));

    ++super::_size;
}

template<typename T, typename SizeT>
template<typename... TArgs>
constexpr array_object<T, SizeT>::reference array_object<T, SizeT>::emplace_first(TArgs&&... args)
{
    grow(super::size() + 1, 1);

    construct_at(static_cast<T*>(super::_buffer), forward<TArgs>(args)...);

    ++super::_size;

    return super::first();
}

template<typename T, typename SizeT>
template<typename... TArgs>
constexpr array_object<T, SizeT>::reference array_object<T, SizeT>::emplace_last(TArgs&&... args)
{
    grow(super::size() + 1);

    construct_at(static_cast<T*>(super::_buffer) + super::_size, forward<TArgs>(args)...);

    ++super::_size;

    return super::last();
}
template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::remove_at(size_t index)
{
    NXX_ASSERT(index < size());

    for (size_t i = index; i < size() - 1; ++i)
    {
        take(&(*this)[i], &(*this)[i + 1]);
    }

    destroy_at(&last());

    --super::_size;
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::remove_at_swap_last(size_t index)
{
    NXX_ASSERT(index < size());

    swap((*this)[index], last());

    remove_last();
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::remove_one(const_reference value)
{
    const size_t index = index_of(value);

    if (index < size())
    {
        remove_at(index);
    }
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::remove_one_swap_last(const_reference value)
{
    const size_t index = index_of(value);

    if (index < size())
    {
        remove_at_swap_last(index);
    }
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::remove_first()
{
    remove_at(0);
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::remove_first_swap_last()
{
    if (size() >= 2)
    {
        swap(first(), last());
    }

    remove_last();
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::remove_last()
{
    NXX_ASSERT(!is_empty());

    destroy_at(&last());

    --super::_size;
}

template<typename T, typename SizeT>
constexpr size_t array_object<T, SizeT>::index_of(const_reference value) const
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
constexpr void array_object<T, SizeT>::reserve(size_t size)
{
    return grow(size);
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::resize(size_t new_size)
{
    if (new_size < size())
    {
        for (size_t i = new_size; i < size(); ++i)
        {
            destroy_at(&(*this)[i]);
        }
    }
    else if (new_size > size())
    {
        grow(new_size);

        for (size_t i = size(); i < new_size; ++i)
        {
            construct_at(static_cast<T*>(super::_buffer) + i);
        }
    }

    super::_size = static_cast<data_size_type>(new_size);
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::clear()
{
    destroy_range(reinterpret_cast<T*>(super::_buffer),
                  reinterpret_cast<T*>(reinterpret_cast<u8_t*>(super::_buffer) + size() * sizeof(T)));

    super::_size = 0;
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::free()
{
    clear();

    memory_block block(super::_buffer, capacity() * sizeof(T));
    deallocate(block);

    super::_capacity = 0;
}

template<typename T, typename SizeT>
constexpr void array_object<T, SizeT>::grow(size_t min_capacity, size_t offset)
{
    if (min_capacity <= super::capacity())
    {
        if (offset > 0)
        {
            for (size_t i = super::_size; i-- > 0;)
            {
                T* from = reinterpret_cast<T*>(static_cast<u8_t*>(super::_buffer) + i * sizeof(T));
                T* to = reinterpret_cast<T*>(static_cast<u8_t*>(super::_buffer) + (i + offset) * sizeof(T));

                construct(to, from);
            }
        }
        return;
    }

    memory_block new_block = allocate(super::get_next_capacity(min_capacity) * sizeof(T));
    NXX_ASSERT(new_block);

    for (size_t i = 0; i < size(); ++i)
    {
        T* from = reinterpret_cast<T*>(static_cast<u8_t*>(super::_buffer) + i * sizeof(T));
        T* to = reinterpret_cast<T*>(static_cast<u8_t*>(new_block.ptr) + (i + offset) * sizeof(T));

        construct(to, from);
    }

    destroy_range(static_cast<T*>(super::_buffer), reinterpret_cast<T*>(static_cast<u8_t*>(super::_buffer) + size() * sizeof(T)));

    if (!super::is_inplace_buffer())
    {
        memory_block block(super::_buffer, super::_capacity * sizeof(T));
        deallocate(block);
    }

    super::_buffer = new_block.ptr;
    super::_capacity = static_cast<data_size_type>(new_block.size / sizeof(T));
}

template<typename T, typename SizeT>
void array_object<T, SizeT>::construct(T* to, T* from)
{
    static_assert(is_copy_constructible<T> || is_move_constructible<T>);

    if constexpr (is_move_constructible<T>)
    {
        construct_at(to, move(*from));
    }
    else if constexpr (is_copy_constructible<T>)
    {
        construct_at(to, *from);
    }
}

template<typename T, typename SizeT>
void array_object<T, SizeT>::take(T* to, T* from)
{
    static_assert(is_copy_assignable<T> || is_move_assignable<T>);

    if constexpr (is_move_assignable<T>)
    {
        *to = move(*from);
    }
    else if constexpr (is_copy_assignable<T>)
    {
        *to = *from;
    }
}

template<typename T, typename SizeT>
void array_object<T, SizeT>::destroy_range(T* begin, T* end)
{
    for (T* it = begin; it != end; ++it)
    {
        destroy_at(it);
    }
}

} // namespace nxx::details