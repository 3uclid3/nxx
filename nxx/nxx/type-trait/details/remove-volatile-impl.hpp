#pragma once

namespace nxx::details {

template<typename T>
struct remove_volatile_impl
{
    using type = T;
};

template<typename T>
struct remove_volatile_impl<volatile T>
{
    using type = T;
};

} // namespace nxx::details
