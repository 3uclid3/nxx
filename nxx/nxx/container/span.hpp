#pragma once

#include <nxx/container/static_array.hpp>
#include <nxx/def.hpp>
#include <nxx/memory/pointer_traits.hpp>
#include <nxx/type_trait/remove_const_volatile.hpp>

namespace nxx {

inline constexpr size_t dynamic_extent = static_cast<size_t>(-1);

template<typename T, size_t ExtentT = dynamic_extent>
class span;

template<typename T, size_t ExtentT>
class span
{
public:
    using element_type = T;
    using value_type = remove_const_volatile<T>;

    using size_type = size_t;
    using difference_type = ptrdiff_t;

    using pointer = T*;
    using const_pointer = const T*;

    using reference = T&;
    using const_reference = const T&;

    using iterator = pointer;
    using const_iterator = const_pointer;

    static constexpr size_type extent = ExtentT;

public:
    template<size_t SizeT = ExtentT>
    requires(SizeT == 0)
    constexpr span();

    constexpr span(const span&) = default;
    constexpr span& operator=(const span&) = default;
    
    constexpr size_type size() const;
    constexpr bool is_empty() const;

    constexpr const_reference operator[](size_t index) const;
    constexpr reference operator[](size_t index);

    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;

    constexpr const_iterator cbegin() const;
    constexpr const_iterator cend() const;

    constexpr iterator begin();
    constexpr iterator end();

    constexpr const_pointer data() const;
    constexpr pointer data();

private:
    pointer _data{nullptr};
};

template<typename T>
class span<T, dynamic_extent>
{
public:
    using element_type = T;
    using value_type = remove_const_volatile<T>;

    using size_type = size_t;
    using difference_type = ptrdiff_t;

    using pointer = T*;
    using const_pointer = const T*;

    using reference = T&;
    using const_reference = const T&;

    using iterator = pointer;
    using const_iterator = const_pointer;

    static constexpr size_type extent = dynamic_extent;

public:
    constexpr span() = default;

    constexpr span(const span&) = default;
    constexpr span& operator=(const span&) = default;

    template<size_t SizeT>
    constexpr span(element_type (&array)[SizeT]);

    template<typename Otherelement_type, size_t SizeT>
    constexpr span(static_array<Otherelement_type, SizeT>& array);

    template<typename Otherelement_type, size_t SizeT>
    constexpr span(const static_array<Otherelement_type, SizeT>& array);

    template<typename ItT>
    constexpr span(ItT first, size_type size);

    template<typename ItT, typename EndT>
    constexpr span(ItT first, EndT last);

    constexpr size_type size() const;
    constexpr bool is_empty() const;

    constexpr const_reference operator[](size_type index) const;
    constexpr reference operator[](size_type index);

    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;

    constexpr const_iterator cbegin() const;
    constexpr const_iterator cend() const;

    constexpr iterator begin();
    constexpr iterator end();

    constexpr const_pointer data() const;
    constexpr pointer data();

private:
    pointer _data{nullptr};
    size_type _size{0};
};

template<typename T, size_t ExtentT>
template<size_t SizeT>
requires(SizeT == 0)
constexpr span<T, ExtentT>::span()
{}

template<typename T, size_t ExtentT>
constexpr span<T, ExtentT>::size_type span<T, ExtentT>::size() const
{
    return ExtentT;
}

template<typename T, size_t ExtentT>
constexpr bool span<T, ExtentT>::is_empty() const
{
    return size() == 0;
}

template<typename T, size_t ExtentT>
constexpr span<T, ExtentT>::const_reference span<T, ExtentT>::operator[](size_type index) const
{
    NXX_ASSERT(index < ExtentT);
    return _data[index];
}

template<typename T, size_t ExtentT>
constexpr span<T, ExtentT>::reference span<T, ExtentT>::operator[](size_type index)
{
    NXX_ASSERT(index < ExtentT);
    return _data[index];
}

template<typename T, size_t ExtentT>
constexpr span<T, ExtentT>::const_iterator span<T, ExtentT>::begin() const
{
    return _data;
}

template<typename T, size_t ExtentT>
constexpr span<T, ExtentT>::const_iterator span<T, ExtentT>::end() const
{
    return _data + ExtentT;
}

template<typename T, size_t ExtentT>
constexpr span<T, ExtentT>::const_iterator span<T, ExtentT>::cbegin() const
{
    return begin();
}

template<typename T, size_t ExtentT>
constexpr span<T, ExtentT>::const_iterator span<T, ExtentT>::cend() const
{
    return end();
}

template<typename T, size_t ExtentT>
constexpr span<T, ExtentT>::const_pointer span<T, ExtentT>::data() const
{
    return _data;
}

template<typename T, size_t ExtentT>
constexpr span<T, ExtentT>::pointer span<T, ExtentT>::data()
{
    return _data;
}

template<typename T, size_t ExtentT>
constexpr span<T, ExtentT>::iterator span<T, ExtentT>::begin()
{
    return _data;
}

template<typename T, size_t ExtentT>
constexpr span<T, ExtentT>::iterator span<T, ExtentT>::end()
{
    return _data + ExtentT;
}

template<typename T>
template<size_t SizeT>
constexpr span<T, dynamic_extent>::span(element_type (&array)[SizeT])
    : _data(to_address(array))
    , _size(SizeT)
{}

template<typename T>
template<typename Otherelement_type, size_t SizeT>
constexpr span<T, dynamic_extent>::span(static_array<Otherelement_type, SizeT>& array)
    : _data(array.data())
    , _size(SizeT)
{
}

template<typename T>
template<typename Otherelement_type, size_t SizeT>
constexpr span<T, dynamic_extent>::span(const static_array<Otherelement_type, SizeT>& array)
    : _data(array.data())
    , _size(SizeT)
{
}

template<typename T>
template<typename ItT>
constexpr span<T, dynamic_extent>::span(ItT first, size_type size)
    : _data(to_address(first))
    , _size(size)
{}

template<typename T>
template<typename ItT, typename EndT>
constexpr span<T, dynamic_extent>::span(ItT first, EndT last)
    : _data(to_address(first))
    , _size(last - first)
{}

template<typename T>
constexpr span<T, dynamic_extent>::size_type span<T, dynamic_extent>::size() const
{
    return _size;
}

template<typename T>
constexpr bool span<T, dynamic_extent>::is_empty() const
{
    return size() == 0;
}

template<typename T>
constexpr span<T, dynamic_extent>::const_reference span<T, dynamic_extent>::operator[](size_type index) const
{
    NXX_ASSERT(index < _size);
    return _data[index];
}

template<typename T>
constexpr span<T, dynamic_extent>::reference span<T, dynamic_extent>::operator[](size_type index)
{
    NXX_ASSERT(index < _size);
    return _data[index];
}

template<typename T>
constexpr span<T, dynamic_extent>::const_iterator span<T, dynamic_extent>::begin() const
{
    return _data;
}

template<typename T>
constexpr span<T, dynamic_extent>::const_iterator span<T, dynamic_extent>::end() const
{
    return _data + _size;
}

template<typename T>
constexpr span<T, dynamic_extent>::const_iterator span<T, dynamic_extent>::cbegin() const
{
    return begin();
}

template<typename T>
constexpr span<T, dynamic_extent>::const_iterator span<T, dynamic_extent>::cend() const
{
    return end();
}

template<typename T>
constexpr span<T, dynamic_extent>::iterator span<T, dynamic_extent>::begin()
{
    return _data;
}

template<typename T>
constexpr span<T, dynamic_extent>::iterator span<T, dynamic_extent>::end()
{
    return _data + _size;
}

template<typename T>
constexpr span<T, dynamic_extent>::const_pointer span<T, dynamic_extent>::data() const
{
    return _data;
}

template<typename T>
constexpr span<T, dynamic_extent>::pointer span<T, dynamic_extent>::data()
{
    return _data;
}

} // namespace nxx
