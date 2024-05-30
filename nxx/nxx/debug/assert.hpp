#pragma once

#include <stddef.h>

namespace nxx::details {

void trigger_assert(const char* condition, const char* message, const char* file, size_t line);

} // namespace nxx::details

// eventually supports format string here
#define _NXX_ASSERT_MSG(condition, message, ...) \
    do { \
        if (!(condition)) \
        { \
            nxx::details::trigger_assert(#condition, message, __FILE__, __LINE__); \
        } \
    } while (false)

#define _NXX_ASSERT_NO_MSG(condition) \
    do { \
        if (!(condition)) nxx::details::trigger_assert(#condition, "", __FILE__, __LINE__); \
    } while (false)

#define _NXX_ASSERT_MSG_OR_NO_MSG_SELECTOR(a, b, assert_macro, ...) assert_macro
#define NXX_ASSERT(...) _NXX_ASSERT_MSG_OR_NO_MSG_SELECTOR(__VA_ARGS__, _NXX_ASSERT_MSG, _NXX_ASSERT_NO_MSG)(__VA_ARGS__)
