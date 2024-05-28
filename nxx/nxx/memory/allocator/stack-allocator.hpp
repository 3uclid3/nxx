#pragma once

#include <nxx/container/static-array.hpp>
#include <nxx/memory/alignment.hpp>
#include <nxx/memory/memory-block.hpp>

namespace nxx {

template<size_t SizeT, size_t AlignmentT = size_t{16}>
class stack_allocator
{
public:
    static constexpr size_t max_size{SizeT};
    static constexpr size_t alignment{AlignmentT};

    [[nodiscard]] constexpr bool owns(const_memory_block block) const;
    [[nodiscard]] constexpr memory_block allocate(size_t size);
    constexpr void deallocate(memory_block block);

private:
    constexpr bool is_last_allocated_block(const_memory_block block) const;

private:
    static_array<u8_t, SizeT> _data;
    u8_t* _pointer{_data.data()};
};

template<size_t SizeT, size_t AlignmentT>
constexpr bool stack_allocator<SizeT, AlignmentT>::owns(const_memory_block block) const
{
    return block.pointer >= _data.begin() && block.pointer < _data.end();
}

template<size_t SizeT, size_t AlignmentT>
constexpr memory_block stack_allocator<SizeT, AlignmentT>::allocate(size_t size)
{
    if (size == 0)
    {
        return nullblk;
    }

    const size_t aligned_size = round_to_alignment(size, alignment);

    u8_t* end_pointer = reinterpret_cast<u8_t*>(reinterpret_cast<uintptr_t>(_pointer) + aligned_size);

    if (end_pointer > _data.end())
    {
        return nullblk;
    }

    memory_block block{_pointer, aligned_size};

    _pointer = end_pointer;

    return block;
}

template<size_t SizeT, size_t AlignmentT>
constexpr void stack_allocator<SizeT, AlignmentT>::deallocate(memory_block block)
{
    if (block == nullblk)
    {
        return;
    }

    if (is_last_allocated_block(block))
    {
        _pointer = static_cast<u8_t*>(block.pointer);
    }
}

template<size_t SizeT, size_t AlignmentT>
constexpr bool stack_allocator<SizeT, AlignmentT>::is_last_allocated_block(const_memory_block block) const
{
    return _pointer == static_cast<const u8_t*>(block.pointer) + block.size;
}

} // namespace nxx
