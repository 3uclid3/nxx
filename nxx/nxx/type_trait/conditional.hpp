#pragma once

#include <nxx/type_trait/details/conditional_impl.hpp>

namespace nxx {

template<bool ConditionT, typename TrueT, typename FalseT>
using conditional = details::conditional_impl<ConditionT, TrueT, FalseT>::type;

} // namespace nxx