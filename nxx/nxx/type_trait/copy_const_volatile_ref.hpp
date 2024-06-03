#pragma once

namespace nxx {

namespace details {

template<class FromT, class ToT>
struct copy_const_volatile_ref_impl
{
    using type = __copy_cv_t<FromT, ToT>;
};

template<class FromT, class ToT>
struct copy_const_volatile_ref_impl<FromT&, ToT>
{
    using type = __add_lvalue_reference_t<__copy_cv_t<FromT, ToT>>;
};

template<class FromT, class ToT>
struct copy_const_volatile_ref_impl<FromT&&, ToT>
{
    using type = __add_rvalue_reference_t<__copy_cv_t<FromT, ToT>>;
};

} // namespace details

template<class FromT, class ToT>
using copy_const_volatile_ref = typename copy_const_volatile_ref_impl<FromT, ToT>::type;

} // namespace nxx