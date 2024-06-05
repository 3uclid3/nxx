#pragma once

#include <nxx/def.hpp>

namespace nxx {

struct memory_block
{
    constexpr memory_block() = default;
    constexpr memory_block(void* ptr, size_t size);

    constexpr memory_block(memory_block&& other);
    constexpr memory_block& operator=(memory_block&& other);

    constexpr memory_block(const memory_block&) = default;
    constexpr memory_block& operator=(const memory_block&) = default;

    [[nodiscard]] constexpr operator bool() const;
    [[nodiscard]] constexpr bool operator==(const memory_block& other) const;

    void* ptr{nullptr};
    size_t size{0};
};

constexpr memory_block::memory_block(void* ptr, size_t size)
    : ptr{ptr}, size{size}
{
}

constexpr memory_block::memory_block(memory_block&& other)
{
    *this = other;
}

constexpr memory_block& memory_block::operator=(memory_block&& other)
{
    ptr = other.ptr;
    size = other.size;
    other.ptr = nullptr;
    other.size = 0;
    return *this;
}

constexpr memory_block::operator bool() const
{
    return size != 0;
}

constexpr bool memory_block::operator==(const memory_block& other) const
{
    return ptr == other.ptr && size == other.size;
}

inline static constexpr memory_block nullblk{nullptr, 0};

} // namespace nxx
