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

    constexpr const prefix* get_prefix(const memory_block& block) const;
    constexpr const suffix* get_suffix(const memory_block& block) const;

    constexpr prefix* get_prefix(const memory_block& block);
    constexpr suffix* get_suffix(const memory_block& block);

private:
    // outer block are always aligned
    constexpr memory_block outer_to_unaligned_inner(const memory_block& outer_block, size_t size) const;

    constexpr memory_block aligned_inner_to_outer(const memory_block& aligned_inner_block) const;
    constexpr memory_block unaligned_inner_to_outer(const memory_block& unaligned_inner_block) const;

    constexpr const prefix* prefix_from_outer(const memory_block& outer_block) const;
    constexpr const suffix* suffix_from_outer(const memory_block& outer_block) const;

    constexpr prefix* prefix_from_outer(const memory_block& outer_block);
    constexpr suffix* suffix_from_outer(const memory_block& outer_block);

private:
    enum class affix_type
    {
        prefix,
        suffix
    };

    template<typename AffixT, affix_type AffixTypeT>
    struct affix_mover
    {
        affix_mover(affix_allocator& allocator, const memory_block& outer_block)
            : cache(move(*affix_getter(allocator, outer_block)))
        {
            destroy_at(affix_getter(allocator, outer_block));
        }

        constexpr void move_to(affix_allocator& allocator, const memory_block& outer_block)
        {
            construct_at(affix_getter(allocator, outer_block), move(cache));
        }

        AffixT* affix_getter(affix_allocator& allocator, const memory_block& outer_block)
        {
            if constexpr (AffixTypeT == affix_type::prefix)
            {
                return allocator.prefix_from_outer(outer_block);
            }
            else if constexpr (AffixTypeT == affix_type::suffix)
            {
                return allocator.suffix_from_outer(outer_block);
            }
            return nullptr;
        }

        AffixT cache;
    };

    template<affix_type AffixTypeT>
    struct affix_mover<no_memory_affix, AffixTypeT>
    {
        constexpr affix_mover(affix_allocator&, const memory_block&)
        {
        }

        constexpr void move_to(affix_allocator&, const memory_block&)
        {
        }
    };

    using prefix_mover = affix_mover<PrefixT, affix_type::prefix>;
    using suffix_mover = affix_mover<SuffixT, affix_type::suffix>;
};

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr memory_block affix_allocator<AllocatorT, PrefixT, SuffixT>::allocate(size_t size)
{
    if (size == 0)
    {
        return nullblk;
    }

    const size_t aligned_size = round_to_alignment(size, alignment);
    memory_block outer_block = allocator::allocate(aligned_size + prefix_size + suffix_size);

    if (!outer_block)
    {
        return nullblk;
    }

    if constexpr (has_prefix) construct_at(prefix_from_outer(outer_block));
    if constexpr (has_suffix) construct_at(suffix_from_outer(outer_block));

    return outer_to_unaligned_inner(outer_block, size);
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
template<typename U>
requires(allocator_traits::has_owns<U>)
constexpr bool affix_allocator<AllocatorT, PrefixT, SuffixT>::owns(const memory_block& block) const
{
    return block && allocator::owns(unaligned_inner_to_outer(block));
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

    memory_block outer_block = unaligned_inner_to_outer(block);

    suffix_mover suffix_mover{*this, outer_block};

    const size_t aligned_delta = round_to_alignment(delta, alignment);
    const bool expand_result = allocator::expand(outer_block, aligned_delta);

    suffix_mover.move_to(*this, outer_block);

    if (!expand_result)
    {
        return false;
    }

    block = outer_to_unaligned_inner(outer_block, block.size + delta);
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

    memory_block outer_block = unaligned_inner_to_outer(block);

    prefix_mover prefix_mover{*this, outer_block};
    suffix_mover suffix_mover{*this, outer_block};

    const size_t aligned_size = round_to_alignment(new_size, alignment);
    const bool reallocate_result = allocator::reallocate(outer_block, aligned_size + prefix_size + suffix_size);

    prefix_mover.move_to(*this, outer_block);
    suffix_mover.move_to(*this, outer_block);

    if (!reallocate_result)
    {
        return false;
    }

    block = outer_to_unaligned_inner(outer_block, new_size);
    return true;
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr void affix_allocator<AllocatorT, PrefixT, SuffixT>::deallocate(memory_block& block)
{
    if (!block)
    {
        return;
    }

    memory_block outer_block = unaligned_inner_to_outer(block);

    if constexpr (has_prefix) destroy_at(prefix_from_outer(outer_block));
    if constexpr (has_suffix) destroy_at(suffix_from_outer(outer_block));

    allocator::deallocate(outer_block);

    block = nullblk;
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr const affix_allocator<AllocatorT, PrefixT, SuffixT>::prefix* affix_allocator<AllocatorT, PrefixT, SuffixT>::get_prefix(const memory_block& block) const
{
    if constexpr (prefix_size > 0)
    {
        NXX_ASSERT(owns(block));
        return prefix_from_outer(unaligned_inner_to_outer(block));
    }
    return nullptr;
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr const affix_allocator<AllocatorT, PrefixT, SuffixT>::suffix* affix_allocator<AllocatorT, PrefixT, SuffixT>::get_suffix(const memory_block& block) const
{
    if constexpr (suffix_size > 0)
    {
        NXX_ASSERT(owns(block));
        return suffix_from_outer(unaligned_inner_to_outer(block));
    }
    return nullptr;
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr affix_allocator<AllocatorT, PrefixT, SuffixT>::prefix* affix_allocator<AllocatorT, PrefixT, SuffixT>::get_prefix(const memory_block& block)
{
    return const_cast<prefix*>(as_const(*this).get_prefix(block));
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr affix_allocator<AllocatorT, PrefixT, SuffixT>::suffix* affix_allocator<AllocatorT, PrefixT, SuffixT>::get_suffix(const memory_block& block)
{
    return const_cast<suffix*>(as_const(*this).get_suffix(block));
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr memory_block affix_allocator<AllocatorT, PrefixT, SuffixT>::outer_to_unaligned_inner(const memory_block& outer_block, size_t size) const
{
    return memory_block{outer_block.as<u8_t>() + prefix_size, size};
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr memory_block affix_allocator<AllocatorT, PrefixT, SuffixT>::aligned_inner_to_outer(const memory_block& aligned_inner_block) const
{
    return memory_block{aligned_inner_block.as<u8_t>() - prefix_size, aligned_inner_block.size + prefix_size + suffix_size};
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr memory_block affix_allocator<AllocatorT, PrefixT, SuffixT>::unaligned_inner_to_outer(const memory_block& unaligned_inner_block) const
{
    const size_t aligned_size = round_to_alignment(unaligned_inner_block.size, alignment);
    return memory_block{unaligned_inner_block.as<u8_t>() - prefix_size, aligned_size + prefix_size + suffix_size};
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr const affix_allocator<AllocatorT, PrefixT, SuffixT>::prefix* affix_allocator<AllocatorT, PrefixT, SuffixT>::prefix_from_outer(const memory_block& outer_block) const
{
    return outer_block.as<const prefix>();
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr const affix_allocator<AllocatorT, PrefixT, SuffixT>::suffix* affix_allocator<AllocatorT, PrefixT, SuffixT>::suffix_from_outer(const memory_block& outer_block) const
{
    return static_cast<const suffix*>(static_cast<const void*>(outer_block.as<const u8_t>() + outer_block.size - suffix_size));
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr affix_allocator<AllocatorT, PrefixT, SuffixT>::prefix* affix_allocator<AllocatorT, PrefixT, SuffixT>::prefix_from_outer(const memory_block& outer_block)
{
    return const_cast<prefix*>(as_const(*this).prefix_from_outer(outer_block));
}

template<typename AllocatorT, typename PrefixT, typename SuffixT>
constexpr affix_allocator<AllocatorT, PrefixT, SuffixT>::suffix* affix_allocator<AllocatorT, PrefixT, SuffixT>::suffix_from_outer(const memory_block& outer_block)
{
    return const_cast<suffix*>(as_const(*this).suffix_from_outer(outer_block));
}

} // namespace nxx
