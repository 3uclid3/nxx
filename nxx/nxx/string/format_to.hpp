#pragma once

#include <nxx/container/span.hpp>
#include <nxx/container/static_array.hpp>
#include <nxx/def.hpp>
#include <nxx/string/cstring.hpp>
#include <nxx/string/format_argument.hpp>
#include <nxx/string/format_specification.hpp>
#include <nxx/string/string_view.hpp>
#include <nxx/string/to_string_view.hpp>

namespace nxx {

template<typename OutT, typename... ArgsT>
void format_to(OutT& out, string_view fmt, const ArgsT&... raw_args);

template<typename OutT>
void vformat_to(OutT& out, string_view fmt, span<format_argument> arguments);

template<typename OutT, typename... ArgsT>
void format_to(OutT& out, string_view fmt, const ArgsT&... raw_args)
{
    static_array args = make_format_arguments(raw_args...);
    vformat_to(out, fmt, span<format_argument>(args));
}

namespace details {

template<typename OutT>
void format_argument_to(OutT& out, format_specification specification, format_argument argument)
{
    auto write_all = [](OutT& out, string_view str) {
        for (char c : str)
        {
            out.write(c);
        }
    };

    static_array<char, 12> raw_buffer;
    span<char> buffer{raw_buffer.data(), raw_buffer.size()};

    switch (argument.get_type())
    {
    case format_argument::type::boolean:
        write_all(out, argument.as_bool() ? "true" : "false");
        break;

    case format_argument::type::character:
        out.write(argument.as_char());
        break;

    case format_argument::type::sint8:
        write_all(out, to_string_view(argument.as_s8(), buffer, specification.get_decimal_base(), specification.is_upper_case()));
        break;

    case format_argument::type::sint16:
        write_all(out, to_string_view(argument.as_s16(), buffer, specification.get_decimal_base(), specification.is_upper_case()));
        break;

    case format_argument::type::sint32:
        write_all(out, to_string_view(argument.as_s32(), buffer, specification.get_decimal_base(), specification.is_upper_case()));
        break;

    case format_argument::type::sint64:
        write_all(out, to_string_view(argument.as_s64(), buffer, specification.get_decimal_base(), specification.is_upper_case()));
        break;

    case format_argument::type::uint8:
        write_all(out, to_string_view(argument.as_u8(), buffer, specification.get_decimal_base(), specification.is_upper_case()));
        break;

    case format_argument::type::uint16:
        write_all(out, to_string_view(argument.as_u16(), buffer, specification.get_decimal_base(), specification.is_upper_case()));
        break;

    case format_argument::type::uint32:
        write_all(out, to_string_view(argument.as_u32(), buffer, specification.get_decimal_base(), specification.is_upper_case()));
        break;

    case format_argument::type::uint64:
        write_all(out, to_string_view(argument.as_u64(), buffer, specification.get_decimal_base(), specification.is_upper_case()));
        break;

    case format_argument::type::raw_string:
        for (char c : argument.as_string())
        {
            out.write(c);
        }
        break;

    case format_argument::type::pointer:
        write_all(out, to_string_view(reinterpret_cast<uintptr_t>(argument.as_pointer()), buffer, specification.get_decimal_base(), specification.is_upper_case()));
        break;
    }
}

} // namespace details

template<typename OutT>
void vformat_to(OutT& out, string_view fmt, span<format_argument> arguments)
{
    size_t next_argument_index = 0;

    const size_t last = fmt.size() - 1;
    for (size_t i = 0; i < fmt.size(); ++i)
    {
        char c = fmt[i];

        if (c != '{')
        {
            out.write(c);
        }
        else // format expression
        {
            NXX_ASSERT(i != last, "Invalid format");

            ++i;

            // parse arg index
            if (is_digit(fmt[i]))
            {
                next_argument_index = 0;
                do {
                    next_argument_index = next_argument_index * 10 + to_digit(fmt[i]);
                } while (++i < fmt.size() && is_digit(fmt[i]));
            }

            format_specification specification;

            // parse format specification
            if (fmt[i] == ':')
            {
                ++i;
                NXX_ASSERT(i != last, "Invalid format");

                if (fmt[i] == '#')
                {
                    specification.is_alternative_form = true;
                    ++i;
                    NXX_ASSERT(i != last, "Invalid format");
                }

                switch (fmt[i])
                {
                case 'b':
                    specification.presentation = format_presentation::binary;
                    break;

                case 'B':
                    specification.presentation = format_presentation::binary_upper_case;
                    break;

                case 'c':
                    specification.presentation = format_presentation::character;
                    break;

                case 'd':
                    specification.presentation = format_presentation::decimal;
                    break;

                case 'o':
                    specification.presentation = format_presentation::octal;
                    break;

                case 'x':
                    specification.presentation = format_presentation::hexadecimal;
                    break;

                case 'X':
                    specification.presentation = format_presentation::hexadecimal_upper_case;
                    break;

                default:
                    NXX_ASSERT(false, "Invalid format");
                    break;
                }

                ++i;
                NXX_ASSERT(i <= last, "Invalid format");
            }

            // we should be at the end, otherwise the format is invalid
            NXX_ASSERT(fmt[i] == '}', "Invalid format");

            details::format_argument_to(out, specification, arguments[next_argument_index++]);
        }
    }
}

} // namespace nxx