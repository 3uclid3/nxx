#pragma once

#include <nxx/def.hpp>

namespace nxx {

struct const_memory_block
{
    const void* pointer;
    size_t size;

    constexpr bool operator==(const const_memory_block&) const = default;

    [[nodiscard]] int compare(const_memory_block other) const;
    [[nodiscard]] int compare(const_memory_block other, size_t compare_size) const;
};

struct memory_block
{
    void* pointer;
    size_t size;

    constexpr bool operator==(const memory_block&) const = default;

    constexpr operator const_memory_block() const;

    [[nodiscard]] int compare(const_memory_block other) const;
    [[nodiscard]] int compare(const_memory_block other, size_t compare_size) const;

    void set(u8_t value);
    void set(u8_t value, size_t set_size);

    void copy(const_memory_block source);
    void copy(const_memory_block source, size_t copy_size);

    void move(const_memory_block source);
    void move(const_memory_block source, size_t move_size);
};

inline constexpr memory_block nullblk{nullptr, 0};
inline constexpr const_memory_block nullcblk{nullptr, 0};

int const_memory_block::compare(const_memory_block other) const
{
    return compare(other, other.size);
}

int const_memory_block::compare(const_memory_block other, size_t compare_size) const
{
    NXX_ASSERT(compare_size <= size);
    return __builtin_memcmp(pointer, other.pointer, compare_size);
}

constexpr memory_block::operator const_memory_block() const
{
    return const_memory_block{pointer, size};
}

int memory_block::compare(const_memory_block other) const
{
    return compare(other, other.size);
}

int memory_block::compare(const_memory_block other, size_t compare_size) const
{
    const const_memory_block this_block = *this;
    return this_block.compare(other, compare_size);
}

void memory_block::set(u8_t value)
{
    set(value, size);
}

void memory_block::set(u8_t value, size_t set_size)
{
    NXX_ASSERT(set_size <= size);
    __builtin_memset(pointer, value, set_size);
}

void memory_block::copy(const_memory_block source)
{
    copy(source, source.size);
}

void memory_block::copy(const_memory_block source, size_t copy_size)
{
    NXX_ASSERT(copy_size <= size);
    __builtin_memcpy(pointer, source.pointer, copy_size);
}

void memory_block::move(const_memory_block source)
{
    move(source, source.size);
}

void memory_block::move(const_memory_block source, size_t move_size)
{
    NXX_ASSERT(move_size <= size);
    __builtin_memmove(pointer, source.pointer, move_size);
}

} // namespace NOS::Memory