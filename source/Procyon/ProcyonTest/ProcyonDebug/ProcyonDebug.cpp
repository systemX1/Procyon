#include "pch.h"

#include <sstream>
#include <streambuf>
#include <cstdio>

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(ProcyonTest, hello) {
    fmtlog::setHeaderPattern("{HMSf} {g:<16} {l}[{t:<6}] ");

    const std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    //testing::internal::CaptureStdout();
    printf("Hello, World!\n");
    FMTLOG(fmtlog::INF, "The answer is {}.", 42);
    fmtlog::poll();

    //const std::string output = testing::internal::GetCapturedStdout();
    //const std::string output = buffer.str();
    //const std::string ans = "The answer is 42.";
    //EXPECT_EQ(ans, output);

    logi("A info msg");
    logd("This msg will not be logged as the default log level is INF");
    fmtlog::setLogLevel(fmtlog::DBG);
    logd("Now debug msg is shown");
}

enum class color { red, green, blue };
template <> struct fmt::formatter<color> : formatter<fmt::string_view> {
    // parse is inherited from formatter<string_view>.
    template <typename FormatContext>
    auto format(color c, FormatContext& ctx) {
        string_view name = "unknown";
        switch (c) {
        case color::red:   name = "red"; break;
        case color::green: name = "green"; break;
        case color::blue:  name = "blue"; break;
        }
        return formatter<string_view>::format(name, ctx);
    }
};

TEST(ProcyonTest, hello2) {
    using namespace fmt::literals;
    logi("I'd rather be {1} than {0}.", "right", "happy");
    logi("Hello, {name}! The answer is {number}. Goodbye, {name}.", "name"_a = "World", "number"_a = 42);

    std::vector<int> v = { 1, 2, 3 };
    logi("ranges: {}", v);

    logi("std::move can be used for objects with non-trivial destructors: {}", std::move(v));
    //assert(v.empty());

    constexpr std::tuple<int, char> t = { 1, 'a' };
    logi("tuples: {}", fmt::join(t, ", "));


    logi("user defined type: {:>10}", color::blue);
    logi("{:*^30}", "centered");
    logi("int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}", 42);
    logi("dynamic precision: {:.{}f}", 3.14, 1);

    // This gives a compile-time error because d is an invalid format specifier for a string.
    // FMT_STRING() is not needed from C++20 onward
    //logi(FMT_STRING("{:d}"), "I am not a number");
}
