#pragma once

#include <nxx/container/span.hpp>
#include <nxx/def.hpp>
#include <nxx/string/format_argument.hpp>
#include <nxx/string/string_view.hpp>

namespace nxx {

template<typename... ArgsT>
string_view format(string_view fmt, const ArgsT&... raw_args);
string_view vformat(string_view fmt, span<format_argument> args);

template<typename... ArgsT>
string_view format(string_view fmt, const ArgsT&... raw_args)
{
    static_array args = make_format_arguments(raw_args...);
    return vformat(fmt, args);
}

} // namespace nxx
