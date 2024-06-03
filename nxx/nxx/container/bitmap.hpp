#pragma once

#include <nxx/string/cstring.hpp>

namespace nxx {

template<typename StorageT>
class bitmap
{
public:
    bitmap() = default;

    explicit constexpr bitmap(const StorageT& data);
    explicit constexpr bitmap(StorageT&& data);

    constexpr bool is_set(size_t index) const;
    constexpr bool is_clear(size_t index) const;

    constexpr void set(size_t index);
    constexpr void clear(size_t index);

    constexpr void reset(u8_t value = 0);

    constexpr size_t size() const;

private:
    StorageT _data;
};

template<typename StorageT>
constexpr bitmap<StorageT>::bitmap(const StorageT& data)
    : _data{data}
{
}

template<typename StorageT>
constexpr bitmap<StorageT>::bitmap(StorageT&& data)
    : _data{std::move(data)}
{
}

template<typename StorageT>
constexpr bool bitmap<StorageT>::is_set(size_t index) const
{
    return _data[index / 8] & (1 << (index % 8));
}

template<typename StorageT>
constexpr bool bitmap<StorageT>::is_clear(size_t index) const
{
    return !is_set(index);
}

template<typename StorageT>
constexpr void bitmap<StorageT>::set(size_t index)
{
    _data[index / 8] |= 1 << (index % 8);
}

template<typename StorageT>
constexpr void bitmap<StorageT>::clear(size_t index)
{
    _data[index / 8] &= ~(1 << (index % 8));
}

template<typename StorageT>
constexpr void bitmap<StorageT>::reset(u8_t value)
{
    memset(_data.data(), static_cast<int>(value), _data.size());
}

template<typename StorageT>
constexpr size_t bitmap<StorageT>::size() const
{
    return _data.size() * 8;
}

} // namespace nxx