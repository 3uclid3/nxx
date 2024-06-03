#pragma once

namespace nxx {

namespace details {

template<class FromT>
struct copy_const_volatile_impl
{
    template<class ToT>
    using copy = ToT;
};

template<class FromT>
struct copy_const_volatile_impl<const FromT>
{
    template<class ToT>
    using copy = const ToT;
};

template<class FromT>
struct copy_const_volatile_impl<volatile FromT>
{
    template<class ToT>
    using copy = volatile ToT;
};

template<class FromT>
struct copy_const_volatile_impl<const volatile FromT>
{
    template<class ToT>
    using copycopy = const volatile ToT;
};
} // namespace details

template<class FromT, class ToT>
using copy_const_volatile = typename details::copy_const_volatile_impl<FromT>::template copy<ToT>;

} // namespace nxx
