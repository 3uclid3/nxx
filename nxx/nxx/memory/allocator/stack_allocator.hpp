#pragma once

#include <nxx/container/static_array.hpp>
#include <nxx/memory/alignment.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

template<size_t SizeT, size_t AlignmentT = default_alignment>
class stack_allocator
{
public:
    using allocator = stack_allocator<SizeT, AlignmentT>;

    static constexpr size_t alignment = AlignmentT;
    static constexpr size_t max_size = SizeT;

public:
    [[nodiscard]] constexpr memory_block allocate(size_t size);
    [[nodiscard]] constexpr bool owns(const memory_block& block) const;
    constexpr bool expand(memory_block& block, size_t delta);
    constexpr bool reallocate(memory_block& block, size_t new_size);
    constexpr void deallocate(memory_block& block);
    constexpr void deallocate_all();

private:
    constexpr bool is_last_allocated_block(const memory_block& block) const;

private:
    alignas(AlignmentT) u8_t _data[SizeT];
    u8_t* _ptr{_data};
};

template<size_t SizeT, size_t AlignmentT>
constexpr memory_block stack_allocator<SizeT, AlignmentT>::allocate(size_t size)
{
    if (size == 0)
    {
        return nullblk;
    }

    const size_t aligned_size = round_to_alignment(size, alignment);

    if (_ptr + aligned_size > _data + SizeT)
    {
        return nullblk;
    }

    memory_block block{_ptr, aligned_size};

    _ptr += aligned_size;

    return block;
}

template<size_t SizeT, size_t AlignmentT>
constexpr bool stack_allocator<SizeT, AlignmentT>::owns(const memory_block& block) const
{
    return block && block.ptr >= _data && block.ptr < _data + SizeT;
}

template<size_t SizeT, size_t AlignmentT>
constexpr void stack_allocator<SizeT, AlignmentT>::deallocate(memory_block& block)
{
    if (!block)
    {
        return;
    }

    if (is_last_allocated_block(block))
    {
        _ptr = static_cast<u8_t*>(block.ptr);
    }

    block = nullblk;
}

template<size_t SizeT, size_t AlignmentT>
constexpr bool stack_allocator<SizeT, AlignmentT>::reallocate(memory_block& block, size_t new_size)
{
    if (block.size == new_size)
    {
        return true;
    }

    if (new_size == 0)
    {
        deallocate(block);
        return true;
    }

    if (!block)
    {
        block = allocate(new_size);
        return true;
    }

    const size_t aligned_size = round_to_alignment(new_size, AlignmentT);

    if (is_last_allocated_block(block))
    {
        if (static_cast<u8_t*>(block.ptr) + aligned_size <= _data + SizeT)
        {
            block.size = aligned_size;
            _ptr = static_cast<u8_t*>(block.ptr) + aligned_size;
            return true;
        }

        // out of memory
        return false;
    }

    if (block.size > new_size)
    {
        block.size = round_to_alignment(new_size, AlignmentT);
        return true;
    }

    memory_block new_block = allocate(new_size);

    if (new_block)
    {
        memcpy(new_block.ptr, block.ptr, block.size);
        block = new_block;
        return true;
    }

    return false;
}

template<size_t SizeT, size_t AlignmentT>
constexpr bool stack_allocator<SizeT, AlignmentT>::expand(memory_block& block, size_t delta)
{
    if (delta == 0)
    {
        return true;
    }

    if (!block)
    {
        block = allocate(delta);
        return block;
    }

    if (!is_last_allocated_block(block))
    {
        return false;
    }

    const size_t aligned_delta = round_to_alignment(delta, AlignmentT);

    if (_ptr + aligned_delta > _data + SizeT)
    {
        return false;
    }

    _ptr += aligned_delta;
    block.size += aligned_delta;

    return true;
}

template<size_t SizeT, size_t AlignmentT>
constexpr void stack_allocator<SizeT, AlignmentT>::deallocate_all()
{
    _ptr = _data;
}

template<size_t SizeT, size_t AlignmentT>
constexpr bool stack_allocator<SizeT, AlignmentT>::is_last_allocated_block(const memory_block& block) const
{
    return _ptr == static_cast<const u8_t*>(block.ptr) + block.size;
}

} // namespace nxx
