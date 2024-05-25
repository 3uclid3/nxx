#pragma once

namespace nxx::details {

template<bool ConditionT, typename TrueT, typename FalseT>
struct conditional_impl
{
    using type = TrueT;
};

template<typename TrueT, typename FalseT>
struct conditional_impl<false, TrueT, FalseT>
{
    using type = FalseT;
};

} // namespace nxx::details