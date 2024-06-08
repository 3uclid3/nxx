#pragma once

namespace nxx::impl {

template<bool ConditionT, typename TrueT, typename FalseT>
struct conditional
{
    using type = TrueT;
};

template<typename TrueT, typename FalseT>
struct conditional<false, TrueT, FalseT>
{
    using type = FalseT;
};

} // namespace nxx::impl

namespace nxx {

template<bool ConditionT, typename TrueT, typename FalseT>
using conditional = impl::conditional<ConditionT, TrueT, FalseT>::type;

} // namespace nxx
