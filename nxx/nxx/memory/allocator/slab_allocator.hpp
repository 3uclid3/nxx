#pragma once

#include <nxx/container/static_array.hpp>
#include <nxx/def.hpp>
#include <nxx/memory/allocator/allocator_reallocation.hpp>
#include <nxx/memory/allocator/allocator_traits.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

struct slab
{
    constexpr void* allocate()
    {
        void* ptr = first_free;
        first_free = *(static_cast<void**>(ptr));
        return ptr;
    }

    constexpr void deallocate(memory_block& block)
    {
        deallocate_at(block, 0);
    }

    constexpr void deallocate_at(memory_block& block, uintptr_t block_offset)
    {
        void* object = static_cast<uint8_t*>(block.ptr) + block_offset;
        *(static_cast<void**>(object)) = first_free;
        first_free = object;
    }

    void* first_free{nullptr};
};

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
class slab_allocator : private AllocatorT
{
public:
    using allocator = AllocatorT;

    static constexpr size_t index_for_size(size_t size);
    static constexpr size_t size_at_index(size_t index);

    static constexpr size_t alignment = AllocatorT::alignment;
    static constexpr size_t max_size = size_at_index(sizeof...(SlabSizesT) - 1);

public:
    [[nodiscard]] constexpr memory_block allocate(size_t size);

    template<typename U = AllocatorT>
    requires(allocator_traits::has_owns<U>)
    [[nodiscard]] constexpr bool owns(const memory_block& block) const;

    constexpr bool expand(memory_block& block, size_t delta);
    constexpr bool reallocate(memory_block& block, size_t new_size);
    constexpr void deallocate(memory_block& block);

    template<typename U = AllocatorT>
    requires(allocator_traits::has_deallocate_all<U>)
    constexpr void deallocate_all();

private:
    void allocate_for_slab(slab& slab, size_t index);

    [[nodiscard]] constexpr memory_block unsafe_allocate(size_t size);
    constexpr void unsafe_deallocate(memory_block& block);

    static_array<slab, sizeof...(SlabSizesT)> _slabs{};
};

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
constexpr size_t slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::index_for_size(size_t size)
{
    size_t index = 0;
    (..., (index += (SlabSizesT < size ? 1 : 0)));
    return index;
}

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
constexpr size_t slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::size_at_index(size_t index)
{
    size_t size = 0;
    (..., (size = index-- == 0 ? SlabSizesT : size));
    return size;
}

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
constexpr memory_block slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::allocate(size_t size)
{
    if (size == 0)
    {
        return nullblk;
    }

    if (size > max_size)
    {
        return nullblk;
    }

    return unsafe_allocate(size);
}

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
template<typename U>
requires(allocator_traits::has_owns<U>)
constexpr bool slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::owns(const memory_block& block) const
{
    return block.size <= size_at_index(sizeof...(SlabSizesT) - 1) && allocator::owns(block);
}

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
constexpr bool slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::expand(memory_block& block, size_t delta)
{
    if (!block)
    {
        return false;
    }

    if (delta == 0)
    {
        return true;
    }

    const size_t new_size = block.size + delta;

    if (new_size > max_size)
    {
        return false;
    }

    const size_t index = index_for_size(block.size);
    const size_t new_index = index_for_size(new_size);

    if (index != new_index)
    {
        return false;
    }

    block.size = new_index;
    return true;
}

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
constexpr bool slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::reallocate(memory_block& block, size_t new_size)
{
    if (auto [success, reallocated] = try_default_reallocate(*this, block, new_size); success)
    {
        return reallocated;
    }

    const size_t index = index_for_size(block.size);
    const size_t new_index = index_for_size(new_size);

    if (index == new_index)
    {
        block.size = new_size;
        return true;
    }

    if (memory_block new_block = unsafe_allocate(new_size))
    {
        unsafe_deallocate(block);
        block = new_block;
        return true;
    }

    return false;
}

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
constexpr void slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::deallocate(memory_block& block)
{
    if (!block)
    {
        return;
    }

    size_t index = index_for_size(block.size);

    if (index >= _slabs.size())
    {
        return;
    }

    _slabs[index].deallocate(block);

    block = nullblk;
}
template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
void slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::allocate_for_slab(slab& slab, size_t index)
{
    const size_t object_size = size_at_index(index);
    const size_t minimum_size = object_size * ObjectsPerSlabT;

    memory_block block = AllocatorT::allocate(minimum_size);

    if (!block)
    {
        return;
    }

    const size_t objects_count = block.size / object_size;

    for (size_t i = 0; i < objects_count; ++i)
    {
        slab.deallocate_at(block, i * object_size);
    }
}

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
constexpr memory_block slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::unsafe_allocate(size_t size)
{
    size_t index = index_for_size(size);

    NXX_ASSERT(index < _slabs.size());

    slab& slab = _slabs[index];

    if (slab.first_free == nullptr)
    {
        allocate_for_slab(slab, index);
    }

    return memory_block{slab.allocate(), size};
}

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
constexpr void slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::unsafe_deallocate(memory_block& block)
{
    size_t index = index_for_size(block.size);

    NXX_ASSERT(index >= _slabs.size());

    _slabs[index].free(block);

    block = nullblk;
}

} // namespace nxx
