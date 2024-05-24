#pragma once

#include <stdint.h>

namespace nxx {

using nullptr_t = decltype(nullptr);

using intptr_t = ::intptr_t;
using uintptr_t = ::uintptr_t;
using ptrdiff_t = ::ptrdiff_t;

using s8_t = ::int8_t;
using s16_t = ::int16_t;
using s32_t = ::int32_t;
using s64_t = ::int64_t;

using u8_t = ::uint8_t;
using u16_t = ::uint16_t;
using u32_t = ::uint32_t;
using u64_t = ::uint64_t;

using f32_t = float;
using f64_t = double;

using size_t = ::size_t;

}
 