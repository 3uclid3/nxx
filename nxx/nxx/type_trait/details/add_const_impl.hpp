#pragma once

namespace nxx::details {

template<class T>
struct add_const_impl
{
    using type = const T;
};

} // namespace nxx::details
