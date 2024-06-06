#include <nxx/memory/utility.hpp>

namespace nxx {

int memcmp(const void* lhs, const void* rhs, size_t size)
{
    const u8_t* l = static_cast<const u8_t*>(lhs);
    const u8_t* r = static_cast<const u8_t*>(rhs);
    for (size_t i = 0; i < size; ++i)
    {
        if (l[i] != r[i])
        {
            return l[i] - r[i];
        }
    }
    return 0;
}

void* memcpy(void* dest, const void* src, size_t size)
{
    u8_t* d = static_cast<u8_t*>(dest);
    const u8_t* s = static_cast<const u8_t*>(src);
    for (size_t i = 0; i < size; ++i)
    {
        d[i] = s[i];
    }
    return dest;
}

void* memset(void* ptr, int val, size_t size)
{
    const u8_t uval = static_cast<u8_t>(val);
    u8_t* p = static_cast<u8_t*>(ptr);
    for (size_t i = 0; i < size; ++i)
    {
        p[i] = uval;
    }
    return ptr;
}

void* memmove(void* dest, const void* src, size_t size)
{
    u8_t* d = static_cast<u8_t*>(dest);
    const u8_t* s = static_cast<const u8_t*>(src);

    if (d < s)
    {
        // Non-overlapping buffers; copy forwards
        for (size_t i = 0; i < size; ++i)
        {
            d[i] = s[i];
        }
    }
    else
    {
        // Overlapping buffers; copy backwards
        for (size_t i = size; i != 0; --i)
        {
            d[i - 1] = s[i - 1];
        }
    }

    return dest;
}

} // namespace nxx
