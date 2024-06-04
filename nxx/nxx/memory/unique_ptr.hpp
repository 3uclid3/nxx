#pragma once

#include <nxx/def.hpp>
#include <nxx/memory/new.hpp>
#include <nxx/type_trait/add_lvalue_reference.hpp>
#include <nxx/type_trait/is_base_of.hpp>
#include <nxx/type_trait/is_same.hpp>
#include <nxx/utility/forward.hpp>

namespace nxx {

template<typename T>
struct default_deleter
{
    void operator()(T* pointer)
    {
        delete pointer;
    }
};

template<typename T, typename DeleterT = default_deleter<T>>
class unique_ptr : private DeleterT
{
public:
    using pointer = T*;

public:
    constexpr unique_ptr() = default;
    constexpr unique_ptr(nullptr_t);

    explicit unique_ptr(T* pointer);

    template<typename U, typename TUDeleter>
    unique_ptr(unique_ptr<U, TUDeleter>&& other);

    unique_ptr(unique_ptr&& other);
    unique_ptr& operator=(unique_ptr&& other);

    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;

    ~unique_ptr();

public:
    [[nodiscard]] T* get() const;
    [[nodiscard]] T* release();

    [[nodiscard]] operator bool() const;

    [[nodiscard]] add_lvalue_reference<T> operator*() const;
    [[nodiscard]] T* operator->() const;

private:
    T* _pointer{nullptr};
};

template<class T, class... TArguments>
inline constexpr unique_ptr<T> make_unique(TArguments&&... args)
{
    return unique_ptr<T>(new T(forward<TArguments>(args)...));
}

template<typename T, typename DeleterT>
class unique_ptr<T[], DeleterT>
{
};

template<typename T, typename DeleterT>
constexpr unique_ptr<T, DeleterT>::unique_ptr(nullptr_t)
{}

template<typename T, typename DeleterT>
unique_ptr<T, DeleterT>::unique_ptr(T* pointer)
    : _pointer(pointer)
{
}
template<typename T, typename DeleterT>
template<typename U, typename TUDeleter>
unique_ptr<T, DeleterT>::unique_ptr(unique_ptr<U, TUDeleter>&& other)
    : _pointer(other.release())
{
}

template<typename T, typename DeleterT>
unique_ptr<T, DeleterT>::unique_ptr(unique_ptr&& other)
    : _pointer(other.release())
{
}

template<typename T, typename DeleterT>
unique_ptr<T, DeleterT>& unique_ptr<T, DeleterT>::operator=(unique_ptr&& other)
{
    _pointer = other._pointer;
    other._pointer = nullptr;
    return *this;
}

template<typename T, typename DeleterT>
unique_ptr<T, DeleterT>::~unique_ptr()
{
    DeleterT::operator()(_pointer);
}

template<typename T, typename DeleterT>
T* unique_ptr<T, DeleterT>::get() const
{
    return _pointer;
}

template<typename T, typename DeleterT>
T* unique_ptr<T, DeleterT>::release()
{
    T* pointer = _pointer;
    _pointer = nullptr;
    return pointer;
}

template<typename T, typename DeleterT>
unique_ptr<T, DeleterT>::operator bool() const
{
    return _pointer != nullptr;
}

template<typename T, typename DeleterT>
add_lvalue_reference<T> unique_ptr<T, DeleterT>::operator*() const
{
    return *_pointer;
}

template<typename T, typename DeleterT>
T* unique_ptr<T, DeleterT>::operator->() const
{
    return _pointer;
}

} // namespace nxx