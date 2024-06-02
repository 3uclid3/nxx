#pragma once

#include <nxx/def.hpp>
#include <nxx/string/string_view.hpp>

namespace nxx {

class format_argument;

template<typename... ArgsT>
auto make_format_arguments(const ArgsT&... raw_arguments);

class format_argument
{
public:
    enum class type
    {
        boolean,
        character,

        sint8,
        sint16,
        sint32,
        sint64,

        uint8,
        uint16,
        uint32,
        uint64,

        raw_string,

        pointer
    };

    constexpr format_argument(bool v);
    constexpr format_argument(char v);

    constexpr format_argument(s8_t v);
    constexpr format_argument(s16_t v);
    constexpr format_argument(s32_t v);
    constexpr format_argument(s64_t v);

    constexpr format_argument(u8_t v);
    constexpr format_argument(u16_t v);
    constexpr format_argument(u32_t v);
    constexpr format_argument(u64_t v);

    constexpr format_argument(const char* cstr);
    constexpr format_argument(string_view sv);

    constexpr format_argument(const void* pointer);

    [[nodiscard]] constexpr type get_type() const;

    [[nodiscard]] constexpr bool as_bool() const;
    [[nodiscard]] constexpr char as_char() const;

    [[nodiscard]] constexpr s8_t as_s8() const;
    [[nodiscard]] constexpr s16_t as_s16() const;
    [[nodiscard]] constexpr s32_t as_s32() const;
    [[nodiscard]] constexpr s64_t as_s64() const;

    [[nodiscard]] constexpr u8_t as_u8() const;
    [[nodiscard]] constexpr u16_t as_u16() const;
    [[nodiscard]] constexpr u32_t as_u32() const;
    [[nodiscard]] constexpr u64_t as_u64() const;

    [[nodiscard]] constexpr string_view as_string() const;

    [[nodiscard]] constexpr const void* as_pointer() const;

private:
    struct raw_string_view
    {
        const char* pointer;
        size_t size;
    };

    union data
    {
        bool b;
        char c;

        s8_t s8;
        s16_t s16;
        s32_t s32_t;
        s64_t s64;

        u8_t u8;
        u16_t u16;
        u32_t u32;
        u64_t u64;

        raw_string_view sv;

        const void* pointer;
    };

    type _type;
    data _data;
};

template<typename... ArgsT>
auto make_format_arguments(const ArgsT&... args)
{
    if constexpr (sizeof...(ArgsT) > 0)
    {
        return to_static_array<format_argument>({args...});
    }
    else
    {
        return static_array<format_argument, 0>{};
    }
}

constexpr format_argument::format_argument(bool v)
    : _type(type::boolean)
{
    _data.b = v;
}

constexpr format_argument::format_argument(char v)
    : _type(type::character)
{
    _data.c = v;
}

constexpr format_argument::format_argument(s8_t v)
    : _type(type::sint8)
{
    _data.s8 = v;
}

constexpr format_argument::format_argument(s16_t v)
    : _type(type::sint16)
{
    _data.s16 = v;
}

constexpr format_argument::format_argument(s32_t v)
    : _type(type::sint32)
{
    _data.s32_t = v;
}

constexpr format_argument::format_argument(s64_t v)
    : _type(type::sint64)
{
    _data.s64 = v;
}

constexpr format_argument::format_argument(u8_t v)
    : _type(type::uint8)
{
    _data.u8 = v;
}

constexpr format_argument::format_argument(u16_t v)
    : _type(type::uint16)
{
    _data.u16 = v;
}

constexpr format_argument::format_argument(u32_t v)
    : _type(type::uint32)
{
    _data.u32 = v;
}

constexpr format_argument::format_argument(u64_t v)
    : _type(type::uint64)
{
    _data.u64 = v;
}

constexpr format_argument::format_argument(const char* cstr)
    : format_argument(string_view(cstr))
{
}

constexpr format_argument::format_argument(string_view sv)
    : _type(type::raw_string)
{
    _data.sv = raw_string_view{
        .pointer = sv.data(),
        .size = sv.size()};
}

constexpr format_argument::format_argument(const void* pointer)
    : _type(type::pointer)
{
    _data.pointer = pointer;
}

constexpr format_argument::type format_argument::get_type() const
{
    return _type;
}

constexpr bool format_argument::as_bool() const
{
    return _data.b;
}

constexpr char format_argument::as_char() const
{
    return _data.c;
}

constexpr s8_t format_argument::as_s8() const
{
    return _data.s8;
}

constexpr s16_t format_argument::as_s16() const
{
    return _data.s16;
}

constexpr s32_t format_argument::as_s32() const
{
    return _data.s32_t;
}

constexpr s64_t format_argument::as_s64() const
{
    return _data.s64;
}

constexpr u8_t format_argument::as_u8() const
{
    return _data.u8;
}

constexpr u16_t format_argument::as_u16() const
{
    return _data.u16;
}

constexpr u32_t format_argument::as_u32() const
{
    return _data.u32;
}

constexpr u64_t format_argument::as_u64() const
{
    return _data.u64;
}

constexpr string_view format_argument::as_string() const
{
    return {_data.sv.pointer, _data.sv.size};
}

constexpr const void* format_argument::as_pointer() const
{
    return _data.pointer;
}

} // namespace nxx