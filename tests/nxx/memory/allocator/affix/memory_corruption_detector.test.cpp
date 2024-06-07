#include <catch2/catch_test_macros.hpp>

#include <nxx/memory/allocator/affix/memory_corruption_detector.hpp>

namespace nxx {

struct memory_corruption_reporter
{
    template<integral T>
    static void report(const void* ptr, T expected, T actual)
    {
        CAPTURE(ptr);
        CAPTURE(expected);
        CAPTURE(actual);

        has_reported = true;
    }

    inline static bool has_reported{false};
};

using test_detector = memory_corruption_detector<u32_t, 0xDEADBEEF, 32, memory_corruption_reporter>;

struct memory_corruption_detector_fixture
{
    memory_corruption_detector_fixture()
    {
        memory_corruption_reporter::has_reported = false;
    }
};

TEST_CASE("memory_corruption_detector does not report if no corruption", "[memory]")
{
    {
        test_detector detector;
        NXX_UNUSED(detector);
    }

    CHECK_FALSE(memory_corruption_reporter::has_reported);
}

TEST_CASE("memory_corruption_detector does report if corruption", "[memory]")
{
    {
        test_detector detector;
        
        detector.guard[0] = ~test_detector::pattern;
    }

    CHECK(memory_corruption_reporter::has_reported);
}

} // namespace nxx
