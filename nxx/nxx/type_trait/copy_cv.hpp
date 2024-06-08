#pragma once

namespace nxx::impl {

template<class FromT>
struct copy_cv
{
    template<class ToT>
    using type = ToT;
};

template<class FromT>
struct copy_cv<const FromT>
{
    template<class ToT>
    using type = const ToT;
};

template<class FromT>
struct copy_cv<volatile FromT>
{
    template<class ToT>
    using type = volatile ToT;
};

template<class FromT>
struct copy_cv<const volatile FromT>
{
    template<class ToT>
    using type = const volatile ToT;
};

} // namespace nxx::impl

namespace nxx {

template<class FromT, class ToT>
using copy_cv = typename impl::copy_cv<FromT>::template type<ToT>;

} // namespace nxx
