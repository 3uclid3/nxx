#pragma once

#include <nxx/type-trait/underlying-type.hpp>

namespace nxx {

template<typename EnumT>
constexpr underlying_type<EnumT> to_underlying(EnumT e)
{
    return static_cast<underlying_type<EnumT>>(e);
}

} // namespace nxx