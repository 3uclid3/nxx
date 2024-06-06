#pragma once

#include <nxx/def.hpp>
#include <nxx/memory/alignment.hpp>
#include <nxx/memory/allocator/allocator_traits.hpp>
#include <nxx/memory/construct_at.hpp>
#include <nxx/memory/memory_block.hpp>
#include <nxx/memory/voidify.hpp>
#include <nxx/type_trait/is_same.hpp>
#include <nxx/utility/as_const.hpp>
#include <nxx/utility/move.hpp>

namespace nxx {

struct no_memory_affix
{
};

enum class memory_affix_type
{
    prefix,
    suffix
};

template<typename AllocatorT, typename AffixT, memory_affix_type AffixTypeT>
struct affix_replacer
{
    affix_replacer(AllocatorT& allocator, const memory_block& outer_block)
        : cache(move(*affix_getter(allocator, outer_block)))
    {
        destroy_at(affix_getter(allocator, outer_block));
    }

    constexpr void replace(AllocatorT& allocator, const memory_block& outer_block)
    {
        construct_at(affix_getter(allocator, outer_block), move(cache));
    }

    AffixT* affix_getter(AllocatorT& allocator, const memory_block& outer_block)
    {
        if constexpr (AffixTypeT == memory_affix_type::prefix)
        {
            return allocator.get_prefix(outer_block);
        }
        else if constexpr (AffixTypeT == memory_affix_type::suffix)
        {
            return allocator.get_suffix(outer_block);
        }
        return nullptr;
    }

    AffixT cache;
};

template<typename AllocatorT, memory_affix_type AffixTypeT>
struct affix_replacer<AllocatorT, no_memory_affix, AffixTypeT>
{
    constexpr affix_replacer(AllocatorT&, const memory_block&)
    {
    }

    constexpr void replace(AllocatorT&, const memory_block&)
    {
    }
};

template<typename AllocatorT, typename PrefixT, typename SuffixT = no_memory_affix>
class affix_allocator : private AllocatorT
{
public:
    using allocator = AllocatorT;

    using prefix = PrefixT;
    using suffix = SuffixT;

    static constexpr size_t alignment = AllocatorT::alignment;

    static constexpr size_t prefix_size = is_same<PrefixT, no_memory_affix> ? 0 : round_to_alignment(sizeof(PrefixT), alignment);
    static constexpr size_t suffix_size = is_same<SuffixT, no_memory_affix> ? 0 : round_to_alignment(sizeof(SuffixT), alignment);

    static constexpr bool has_prefix = prefix_size > 0;
    static constexpr bool has_suffix = suffix_size > 0;

public:
    [[nodiscard]] constexpr memory_block allocate(size_t size);

    template<typename U = AllocatorT>
    requires(allocator_traits::has_owns<U>)
    [[nodiscard]] constexpr bool owns(const memory_block& block) const;

    template<typename U = AllocatorT>
    requires(allocator_traits::has_expand<U>)
    constexpr bool expand(memory_block& block, size_t delta);
    constexpr bool reallocate(memory_block& block, size_t new_size);
    constexpr void deallocate(memory_block& block);

    constexpr memory_block to_inner_block(const memory_block& block) const;
    constexpr memory_block to_outer_block(const memory_block& block) const;

    constexpr const prefix* get_prefix(const memory_block& outer_block) const;
    constexpr const suffix* get_suffix(const memory_block& outer_block) const;

    constexpr prefix* get_prefix(const memory_block& outer_block);
    constexpr suffix* get_suffix(const memory_block& outer_block);
};

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr memory_block affix_allocator<AllocatorT, PrefixT, SuffixT>::allocate(size_t size)
{
    if (size == 0)
    {
        return nullblk;
    }

    size_t aligned_size = round_to_alignment(size, alignment);
    memory_block outer_block = allocator::allocate(aligned_size + prefix_size + suffix_size);

    if (!outer_block)
    {
        return nullblk;
    }

    if constexpr (has_prefix) construct_at(get_prefix(outer_block));
    if constexpr (has_suffix) construct_at(get_suffix(outer_block));

    return to_inner_block(outer_block);
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
template<typename U>
requires(allocator_traits::has_owns<U>)
constexpr bool affix_allocator<AllocatorT, PrefixT, SuffixT>::owns(const memory_block& block) const
{
    return block && allocator::owns(to_outer_block(block));
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
template<typename U>
requires(allocator_traits::has_expand<U>)
constexpr bool affix_allocator<AllocatorT, PrefixT, SuffixT>::expand(memory_block& block, size_t delta)
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

    memory_block outer_block = to_outer_block(block);
    affix_replacer<affix_allocator, suffix, affix_type::suffix> suffix_replacer{*this, outer_block};

    if (!allocator::expand(outer_block, delta))
    {
        return false;
    }

    suffix_replacer.replace(*this, outer_block);
    block = to_inner_block(outer_block);
    return true;
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr bool affix_allocator<AllocatorT, PrefixT, SuffixT>::reallocate(memory_block& block, size_t new_size)
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

    memory_block outer_block = to_outer_block(block);

    affix_replacer<affix_allocator, prefix, affix_type::prefix> prefix_replacer{*this, outer_block};
    affix_replacer<affix_allocator, suffix, affix_type::suffix> suffix_replacer{*this, outer_block};

    const bool reallocate_result = allocator::reallocate(outer_block, new_size + prefix_size + suffix_size);

    prefix_replacer.replace(*this, outer_block);
    suffix_replacer.replace(*this, outer_block);

    if (!reallocate_result)
    {
        return false;
    }

    block = to_inner_block(outer_block);
    return true;
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr void affix_allocator<AllocatorT, PrefixT, SuffixT>::deallocate(memory_block& block)
{
    if (!block)
    {
        return;
    }

    memory_block outer_block = to_outer_block(block);

    if constexpr (has_prefix) destroy_at(get_prefix(outer_block));
    if constexpr (has_suffix) destroy_at(get_suffix(outer_block));

    allocator::deallocate(outer_block);

    block = nullblk;
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr memory_block affix_allocator<AllocatorT, PrefixT, SuffixT>::to_inner_block(const memory_block& block) const
{
    return memory_block{static_cast<u8_t*>(block.ptr) + prefix_size, block.size - prefix_size - suffix_size};
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr memory_block affix_allocator<AllocatorT, PrefixT, SuffixT>::to_outer_block(const memory_block& block) const
{
    return memory_block{static_cast<u8_t*>(block.ptr) - prefix_size, block.size + prefix_size + suffix_size};
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr const affix_allocator<AllocatorT, PrefixT, SuffixT>::prefix* affix_allocator<AllocatorT, PrefixT, SuffixT>::get_prefix(const memory_block& outer_block) const
{
    if constexpr (prefix_size > 0)
    {
        return static_cast<prefix*>(outer_block.ptr);
    }
    return nullptr;
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr const affix_allocator<AllocatorT, PrefixT, SuffixT>::suffix* affix_allocator<AllocatorT, PrefixT, SuffixT>::get_suffix(const memory_block& outer_block) const
{
    if constexpr (suffix_size > 0)
    {
        return static_cast<suffix*>(static_cast<void*>(static_cast<u8_t*>(outer_block.ptr) + prefix_size + to_inner_block(outer_block).size));
    }
    return nullptr;
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr affix_allocator<AllocatorT, PrefixT, SuffixT>::prefix* affix_allocator<AllocatorT, PrefixT, SuffixT>::get_prefix(const memory_block& outer_block)
{
    return const_cast<prefix*>(as_const(*this).get_prefix(outer_block));
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr affix_allocator<AllocatorT, PrefixT, SuffixT>::suffix* affix_allocator<AllocatorT, PrefixT, SuffixT>::get_suffix(const memory_block& outer_block)
{
    return const_cast<suffix*>(as_const(*this).get_suffix(outer_block));
}

} // namespace nxx
