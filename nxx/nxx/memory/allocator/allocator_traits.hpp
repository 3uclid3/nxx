#pragma once

#include <nxx/type_trait/macro/declare_has_method.macro.hpp>

namespace nxx {
struct memory_block;
}

namespace nxx::allocator_traits {

NXX_TYPE_TRAIT_HAS_METHOD_CONST(has_owns, owns, bool, const memory_block&);
NXX_TYPE_TRAIT_HAS_METHOD(has_expand, expand, bool, memory_block&, size_t);
NXX_TYPE_TRAIT_HAS_METHOD(has_deallocate_all, deallocate_all, void);

} // namespace nxx::allocator_traits
