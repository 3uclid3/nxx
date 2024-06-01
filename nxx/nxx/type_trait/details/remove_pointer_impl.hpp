#pragma once

namespace nxx::details {

template<typename T>
struct remove_pointer_impl
{
    using type = T;
};

template<typename T>
struct remove_pointer_impl<T*>
{
    using type = T;
};

} // namespace nxx::details
