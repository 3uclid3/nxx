#pragma once

#include <nxx/def.hpp>

namespace std {

// required by compilers to be in std namespace
template<class T>
class initializer_list
{
public:
    using value_type = T;
    using reference = const T&;
    using const_reference = const T&;
    using size_type = size_t;

    using iterator = const T*;
    using const_iterator = const T*;

    constexpr initializer_list()
        : __begin_(nullptr)
        , __size_(0) {}

    constexpr size_t size() const { return __size_; }
    constexpr const T* begin() const { return __begin_; }
    constexpr const T* end() const { return __begin_ + __size_; }

private:
    initializer_list(const T* begin, size_t size)
        : __begin_(begin)
        , __size_(size)
    {}

    const T* __begin_;
    size_t __size_;
};

} // namespace std

namespace nxx {

template<typename T>
using InitializerList = std::initializer_list<T>;

} // namespace nxx