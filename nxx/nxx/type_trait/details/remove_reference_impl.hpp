#pragma once

namespace nxx::details {

template<typename T>
struct remove_reference_impl
{
    using type = T;
};

template<typename T>
struct remove_reference_impl<T&>
{
    using type = T;
};

template<typename T>
struct remove_reference_impl<T&&>
{
    using type = T;
};

} // namespace nxx::details
