#pragma once

#include <nxx/container/static_array.hpp>
#include <nxx/def.hpp>
#include <nxx/memory/memory_block.hpp>

namespace nxx {

struct slab
{
    // size_t size{0};
    void* first_free{nullptr};
};

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
class slab_allocator : private AllocatorT
{
public:
    constexpr bool owns(const_memory_block block) const;
    constexpr memory_block allocate(size_t size);
    constexpr void deallocate(memory_block block);

    constexpr size_t index_for_size(size_t size) const;
    constexpr size_t size_at_index(size_t index) const;

private:
    void allocate_for_slab(slab& slab, size_t index);

    static_array<slab, sizeof...(SlabSizesT)> _slabs{};
};

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
constexpr bool slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::owns(const_memory_block block) const
{
    return block.size <= size_at_index(sizeof...(SlabSizesT) - 1) && AllocatorT::owns(block);
}

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
constexpr memory_block slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::allocate(size_t size)
{
    if (size == 0)
    {
        return nullblk;
    }

    size_t index = index_for_size(size);
    if (index >= _slabs.size())
    {
        return nullblk; // size not supported
    }

    slab& slab = _slabs[index];
    if (slab.first_free == nullptr)
    {
        allocate_for_slab(slab, index);
    }

    void* ptr = slab.first_free;
    slab.first_free = *(reinterpret_cast<void**>(ptr));
    return {ptr, size};
}

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
constexpr void slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::deallocate(memory_block block)
{
    if (block.pointer == nullptr || block.size == 0)
    {
        return;
    }

    size_t index = index_for_size(block.size);
    if (index < _slabs.size())
    {
        void* ptr = block.pointer;
        *(reinterpret_cast<void**>(ptr)) = _slabs[index].first_free;
        _slabs[index].first_free = ptr;
    }
}

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
constexpr size_t slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::index_for_size(size_t size) const
{
    size_t index = 0;
    (..., (index += (SlabSizesT < size ? 1 : 0)));
    return index;
}

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
constexpr size_t slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::size_at_index(size_t index) const
{
    size_t size = 0;
    (..., (size = index-- == 0 ? SlabSizesT : size));
    return size;
}

template<typename AllocatorT, size_t ObjectsPerSlabT, size_t... SlabSizesT>
void slab_allocator<AllocatorT, ObjectsPerSlabT, SlabSizesT...>::allocate_for_slab(slab& slab, size_t index)
{
    const size_t object_size = size_at_index(index);
    const size_t minimum_size = object_size * ObjectsPerSlabT;

    memory_block block = AllocatorT::allocate(minimum_size);

    if (block.is_null())
    {
        return;
    }

    const size_t objects_count = block.size / object_size;

    for (size_t i = 0; i < objects_count; ++i)
    {
        void* obj = static_cast<uint8_t*>(block.pointer) + i * object_size;
        *(reinterpret_cast<void**>(obj)) = slab.first_free;
        slab.first_free = obj;
    }
}

} // namespace nxx
