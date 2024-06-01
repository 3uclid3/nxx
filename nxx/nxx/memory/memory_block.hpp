#pragma once

#include <nxx/def.hpp>

namespace nxx {

struct const_memory_block
{
    const void* pointer;
    size_t size;

    [[nodiscard]] constexpr bool operator==(const const_memory_block&) const = default;

    [[nodiscard]] constexpr operator bool() const;

    [[nodiscard]] constexpr bool is_null() const;

    [[nodiscard]] constexpr int compare(const_memory_block other) const;
    [[nodiscard]] constexpr int compare(const_memory_block other, size_t compare_size) const;
};

struct memory_block
{
    void* pointer;
    size_t size;

    [[nodiscard]] constexpr bool operator==(const memory_block&) const = default;

    [[nodiscard]] constexpr operator const_memory_block() const;
    [[nodiscard]] constexpr operator bool() const;

    [[nodiscard]] constexpr bool is_null() const;

    [[nodiscard]] constexpr int compare(const_memory_block other) const;
    [[nodiscard]] constexpr int compare(const_memory_block other, size_t compare_size) const;

    constexpr void set(u8_t value);
    constexpr void set(u8_t value, size_t set_size);

    constexpr void copy(const_memory_block source);
    constexpr void copy(const_memory_block source, size_t copy_size);

    constexpr void move(const_memory_block source);
    constexpr void move(const_memory_block source, size_t move_size);
};

inline constexpr memory_block nullblk{nullptr, 0};
inline constexpr const_memory_block nullcblk{nullptr, 0};

constexpr const_memory_block::operator bool() const
{
    return !is_null();
}

constexpr bool const_memory_block::is_null() const
{
    return pointer == nullptr;
}

constexpr int const_memory_block::compare(const_memory_block other) const
{
    return compare(other, other.size);
}

constexpr int const_memory_block::compare(const_memory_block other, size_t compare_size) const
{
    NXX_ASSERT(compare_size <= size);
    return __builtin_memcmp(pointer, other.pointer, compare_size);
}

constexpr memory_block::operator const_memory_block() const
{
    return const_memory_block{pointer, size};
}

constexpr memory_block::operator bool() const
{
    return !is_null();
}

constexpr bool memory_block::is_null() const
{
    return pointer == nullptr;
}

constexpr int memory_block::compare(const_memory_block other) const
{
    return compare(other, other.size);
}

constexpr int memory_block::compare(const_memory_block other, size_t compare_size) const
{
    const const_memory_block this_block = *this;
    return this_block.compare(other, compare_size);
}

constexpr void memory_block::set(u8_t value)
{
    set(value, size);
}

constexpr void memory_block::set(u8_t value, size_t set_size)
{
    NXX_ASSERT(set_size <= size);
    __builtin_memset(pointer, value, set_size);
}

constexpr void memory_block::copy(const_memory_block source)
{
    copy(source, source.size);
}

constexpr void memory_block::copy(const_memory_block source, size_t copy_size)
{
    NXX_ASSERT(copy_size <= size);
    __builtin_memcpy(pointer, source.pointer, copy_size);
}

constexpr void memory_block::move(const_memory_block source)
{
    move(source, source.size);
}

constexpr void memory_block::move(const_memory_block source, size_t move_size)
{
    NXX_ASSERT(move_size <= size);
    __builtin_memmove(pointer, source.pointer, move_size);
}

} // namespace nxx
