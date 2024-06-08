#pragma once

#include <nxx/type_trait/add_lvalue_reference.hpp>
#include <nxx/type_trait/copy_cv.hpp>

namespace nxx::impl {

template<class FromT, class ToT>
struct copy_cvref : copy_cv<FromT, ToT>
{};

template<class FromT, class ToT>
struct copy_cvref<FromT&, ToT> : add_lvalue_reference<copy_cv<FromT, ToT>::type>
{};

template<class FromT, class ToT>
struct copy_cvref<FromT&&, ToT>: add_lvalue_reference<copy_cv<FromT, ToT>::type>
{};

} // namespace nxx::impl

namespace nxx {

template<class FromT, class ToT>
using copy_cvref = typename impl::copy_cvref<FromT, ToT>::type;

} // namespace nxx