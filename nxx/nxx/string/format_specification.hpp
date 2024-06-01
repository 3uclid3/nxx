#pragma once

namespace nxx {

enum class format_presentation
{
    unset,

    binary,
    binary_upper_case,

    character,
    decimal,
    octal,

    hexadecimal,
    hexadecimal_upper_case
};

struct format_specification
{
    constexpr bool is_upper_case() const;
    constexpr auto get_decimal_base() const;

    format_presentation presentation{format_presentation::unset};
    bool is_alternative_form{false};
};

constexpr bool format_specification::is_upper_case() const
{
    return presentation == format_presentation::binary_upper_case || presentation == format_presentation::hexadecimal_upper_case;
}

constexpr auto format_specification::get_decimal_base() const
{
    switch (presentation)
    {
    case format_presentation::binary:
    case format_presentation::binary_upper_case:
        return 2;

    case format_presentation::octal:
        return 8;

    case format_presentation::hexadecimal:
    case format_presentation::hexadecimal_upper_case:
        return 16;
        
    case format_presentation::character:
    case format_presentation::decimal:
    case format_presentation::unset:
    default:
        return 10;
    }
}

} // namespace nxx