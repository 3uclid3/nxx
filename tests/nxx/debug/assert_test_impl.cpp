#include <nxx/debug/assert.hpp>

#include <sstream>
#include <string>
#include <string_view>

#include <catch2/catch_test_macros.hpp>

namespace nxx::details {

void trigger_assert(const char* condition, const char* message, const char* file, size_t line)
{
    std::string_view message_sv{message};

    std::stringstream ss;
    ss << "Assert '" << condition << "' failed.\n";
    if (!message_sv.empty())
    {
        ss << "\r\rwith message '" << message_sv << "'\n";
    }
    ss << "\t\t in " << file << "(" << line << ")\n";

    std::string string = ss.str();
    FAIL(string.c_str());
}

} // namespace nxx::details