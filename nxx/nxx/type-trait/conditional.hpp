#pragma once

#include <nxx/type-trait/details/conditional-impl.hpp>

namespace nxx {

template<bool ConditionT, typename TrueT, typename FalseT>
using conditional = details::conditional_impl<ConditionT, TrueT, FalseT>::type;

} // namespace nxx