#include <nxx/string/format.hpp>

#include <nxx/container/static-array.hpp>
#include <nxx/string/format-to.hpp>
#include <nxx/utility/as-const.hpp>

namespace nxx {

namespace {

class local_buffers
{
public:
    static constexpr size_t buffer_size = 8192;
    static constexpr size_t buffer_count = 16;
    static constexpr size_t last_buffer_index = buffer_count - 1;

    span<char> next_buffer()
    {
        const size_t offset = _next_buffer_index * buffer_size;
        _next_buffer_index = _next_buffer_index == last_buffer_index ? 0 : _next_buffer_index + 1;
        return {&_buffer[offset], buffer_count};
    }

private:
    static_array<char, buffer_size * buffer_count> _buffer;
    size_t _next_buffer_index{0};
};

struct out_wrapper
{
    void write(char c)
    {
        buffer[size++] = c;
    }

    span<char> buffer;
    size_t size{0};
};

// TODO thread_local
local_buffers buffers;

} // namespace

string_view vformat(string_view fmt, span<format_argument> args)
{
    out_wrapper out{.buffer = buffers.next_buffer()};
    vformat_to(out, fmt, args);
    return string_view{as_const(out).buffer.data(), out.size};
}

} // namespace nxx
