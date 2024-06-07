#pragma once

#include <nxx/algorithm/clamp.hpp>
#include <nxx/def.hpp>

namespace nxx::details {

template<typename SizeT>
class array_data
{
public:
    using data_size_type = SizeT;

    constexpr bool is_empty() const;
    constexpr size_t size() const;
    constexpr size_t capacity() const;

protected:
    constexpr size_t get_next_capacity(size_t minSize) const;

protected:
    constexpr array_data() = default;
    constexpr array_data(void* pointer, size_t capacity);

    void* _buffer{nullptr};
    data_size_type _size{0};
    data_size_type _capacity{0};
};

template<typename SizeT>
constexpr bool array_data<SizeT>::is_empty() const
{
    return size() == 0;
}

template<typename SizeT>
constexpr size_t array_data<SizeT>::size() const
{
    return _size;
}

template<typename SizeT>
constexpr size_t array_data<SizeT>::capacity() const
{
    return _capacity;
}

template<typename SizeT>
constexpr array_data<SizeT>::array_data(void* buffer, size_t capacity)
    : _buffer(buffer)
    , _capacity(static_cast<data_size_type>(capacity))
{
}

template<typename SizeT>
constexpr size_t array_data<SizeT>::get_next_capacity(size_t min_size) const
{
    constexpr size_t max_size = static_cast<SizeT>(-1);

    NXX_ASSERT(min_size <= max_size);
    NXX_ASSERT(_capacity < max_size);

    const size_t new_capacity = _capacity * 2 + 1;
    return clamp(new_capacity, min_size, max_size);
}

} // namespace nxx::details