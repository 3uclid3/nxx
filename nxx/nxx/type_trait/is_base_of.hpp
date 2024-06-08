#pragma once

#include <nxx/type_trait/integral_constant.hpp>

namespace nxx::impl {

template<typename BaseT, typename DerivedT>
struct is_base_of : bool_constant<__is_base_of(BaseT, DerivedT)>
{};

} // namespace nxx::impl

namespace nxx {

template<typename BaseT, typename DerivedT>
inline constexpr bool is_base_of = impl::is_base_of<BaseT, DerivedT>::value;

} // namespace nxx
