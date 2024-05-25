#pragma once

namespace nxx::details {

template<typename T>
struct remove_const_impl
{
    using type = T;
};

template<typename T>
struct remove_const_impl<const T>
{
    using type = T;
};

} // namespace nxx::details
