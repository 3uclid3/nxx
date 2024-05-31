#pragma once

#include <nxx/algorithm/min.hpp>
#include <nxx/def.hpp>
#include <nxx/string/cstring.hpp>

namespace nxx {

template<typename CharT>
class basic_string_view
{
public:
    using char_type = CharT;
    using size_type = size_t;

    static constexpr size_type npos{static_cast<size_type>(-1)};

    constexpr basic_string_view() = default;
    constexpr basic_string_view(const basic_string_view&) = default;
    constexpr basic_string_view(basic_string_view&&) = default;

    constexpr basic_string_view(nullptr_t) = delete;

    constexpr basic_string_view(const char_type* str, size_type size);
    constexpr basic_string_view(const char_type* cstr);

    template<typename ItT, typename EndT>
    constexpr basic_string_view(ItT first, EndT end);

    constexpr basic_string_view& operator=(const basic_string_view&) = default;
    constexpr basic_string_view& operator=(basic_string_view&&) = default;

    constexpr bool operator==(const basic_string_view& other) const;

    constexpr char_type operator[](size_type index) const;

    constexpr size_type size() const;
    constexpr bool is_empty() const;

    constexpr const char_type* data() const;

    constexpr auto begin() const;
    constexpr auto end() const;

    constexpr auto begin();
    constexpr auto end();

    constexpr size_type find_last_of(char_type ch) const;

    constexpr basic_string_view substr(size_type offset, size_type size = npos) const;

private:
    const char_type* _data{nullptr};
    size_type _size{0};
};

using string_view = basic_string_view<char>;

template<typename CharT>
constexpr basic_string_view<CharT>::basic_string_view(const char_type* str, size_type size)
    : _data(str)
    , _size(size)
{
}

template<typename CharT>
constexpr basic_string_view<CharT>::basic_string_view(const char_type* cstr)
    : _data(cstr)
    , _size(strlen(cstr))
{
}

template<typename CharT>
template<typename ItT, typename EndT>
constexpr basic_string_view<CharT>::basic_string_view(ItT first, EndT end)
    : _data(first)
    , _size(end - first)
{
}

template<typename CharT>
constexpr bool basic_string_view<CharT>::operator==(const basic_string_view& other) const
{
    if (size() != other.size())
    {
        return false;
    }

    for (size_type i = 0; i < size(); ++i)
    {
        if (_data[i] != other._data[i])
        {
            return false;
        }
    }

    return true;
}

template<typename CharT>
constexpr typename basic_string_view<CharT>::char_type basic_string_view<CharT>::operator[](size_type index) const
{
    return _data[index];
}

template<typename CharT>
constexpr basic_string_view<CharT>::size_type basic_string_view<CharT>::size() const
{
    return _size;
}

template<typename CharT>
constexpr bool basic_string_view<CharT>::is_empty() const
{
    return _size <= 0;
}

template<typename CharT>
constexpr const typename basic_string_view<CharT>::char_type* basic_string_view<CharT>::data() const
{
    return _data;
}

template<typename CharT>
constexpr auto basic_string_view<CharT>::begin() const
{
    return _data;
}

template<typename CharT>
constexpr auto basic_string_view<CharT>::end() const
{
    return _data + _size;
}

template<typename CharT>
constexpr auto basic_string_view<CharT>::begin()
{
    return _data;
}

template<typename CharT>
constexpr auto basic_string_view<CharT>::end()
{
    return _data + _size;
}

template<typename CharT>
constexpr basic_string_view<CharT>::size_type basic_string_view<CharT>::find_last_of(char_type ch) const
{
    if (!is_empty())
    {
        for (size_type i = size() - 1; true; --i)
        {
            if (_data[i] == ch)
            {
                return i;
            }

            if (i == 0)
            {
                break;
            }
        }
    }

    return npos;
}

template<typename CharT>
constexpr basic_string_view<CharT> basic_string_view<CharT>::substr(size_type offset, size_type size) const
{
    size = min(size, _size - offset);
    size = min(size, _size);
    return size == 0 ? basic_string_view<char_type>{} : basic_string_view<char_type>{_data + offset, size};
}

} // namespace nxx