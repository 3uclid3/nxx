#pragma once

namespace nxx::details {

template<class T>
struct add_volatile_impl
{
    using type = volatile T;
};

} // namespace nxx::details
