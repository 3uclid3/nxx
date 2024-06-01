#pragma once

namespace nxx {

template<typename T>
class ref_wrap
{
public:
    using Type = T;

    constexpr ref_wrap(T& ptr)
        : _ptr(&ptr) {}

    constexpr operator Type&() const { return *_ptr; }
    constexpr Type& get() const { return *_ptr; }

private:
    T* _ptr;
};

template<class T>
void ref(const T&&) = delete;

template<class T>
void cref(const T&&) = delete;

template<typename T>
constexpr ref_wrap<T> ref(T& v)
{
    return ref_wrap<T>(v);
}

template<typename T>
constexpr ref_wrap<T> ref(ref_wrap<T> v)
{
    return v;
}

template<typename T>
constexpr ref_wrap<const T> cref(const T& v)
{
    return ref_wrap<const T>(v);
}

template<typename T>
constexpr ref_wrap<const T> cref(ref_wrap<T> v)
{
    return ref_wrap<const T>(v.get());
}
} // namespace nxx