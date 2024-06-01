#pragma once

#include <nxx/concept/integral.hpp>
#include <nxx/container/span.hpp>
#include <nxx/def.hpp>
#include <nxx/string/string_view.hpp>
#include <nxx/type_trait/is_signed.hpp>

namespace nxx {

const string_view to_string_view(integral auto value, span<char> buffer, int base = 10, bool upper_case = false)
{
    static constexpr string_view lower_cases_entries{"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"};
    static constexpr string_view upper_cases_entries{"ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    if (base < 2 || base > 36)
    {
        return string_view{};
    }

    string_view entries = upper_case ? upper_cases_entries : lower_cases_entries;

    char* ptr = buffer.data();

    decltype(value) base_as_value_type = static_cast<decltype(value)>(base);
    decltype(value) tmp_value;

    do {
        tmp_value = value;
        value /= base_as_value_type;
        *ptr++ = entries[static_cast<string_view::size_type>(35 + (tmp_value - value * base_as_value_type))];
    } while (value);

    if constexpr (is_signed<decltype(value)>)
    {
        if (tmp_value < 0)
            *ptr++ = '-';
    }

    const size_t size = static_cast<size_t>(ptr - buffer.data());

    *ptr-- = '\0';

    // Reverse the string
    char* front = buffer.data();
    while (front < ptr)
    {
        char tmp_char = *ptr;
        *ptr-- = *front;
        *front++ = tmp_char;
    }

    return {buffer.cbegin(), size};
}

} // namespace NOS