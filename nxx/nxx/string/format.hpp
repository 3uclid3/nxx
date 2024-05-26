#pragma once

#include <nxx/def.hpp>
#include <nxx/container/span.hpp>
#include <nxx/string/format-argument.hpp>
#include <nxx/string/string-view.hpp>

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

} // namespace NOS
