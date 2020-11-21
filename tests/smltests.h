#ifndef SLIPPYS_MATH_LIBRARY_TESTS_H
#define SLIPPYS_MATH_LIBRARY_TESTS_H

#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#define LOCATION_TEXT_COLOUR "\033[94;1m"
#define FAILURE_TEXT_COLOUR "\033[91m"
#define NORMAL_TEXT_COLOUR "\033[0m"
#define NORMAL_TEXT_COLOUR_BOLD "\033[0;1m"
#define SUCCESS_TEXT_COLOUR "\033[92;1m"
#define CLASS_TEXT_COLOUR "\033[95;1m"

#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION_MESSAGE LOCATION_TEXT_COLOUR __FILE__ "(" S2(__LINE__) "):" NORMAL_TEXT_COLOUR
#define ASSERTION_FAIL_MESSAGE \
    LOCATION_MESSAGE FAILURE_TEXT_COLOUR " Assertion failed! ❌ " NORMAL_TEXT_COLOUR

#define TEST_NAME(method, situation, expectation) method##_##situation##_##expectation

namespace SML {
namespace Tests {

static uint32_t ERROR_COUNT = 0;

template <typename T>
struct TestRunner {
   public:
    TestRunner();

    static void run() {
        const TestRunner<T> runner = TestRunner<T>();
        for (auto const test : runner._tests) {
            test();
        }
    }

   private:
    std::vector<std::function<void(void)>> _tests;
};

#define ASSERT(expr, error_msg)                                                        \
    std::cout << "\t" << CLASS_TEXT_COLOUR << CLASS_NAME << NORMAL_TEXT_COLOUR << ": " \
              << CURRENT_TEST << " ";                                                  \
    if (!(expr)) {                                                                     \
        std::cerr << ASSERTION_FAIL_MESSAGE << error_msg << std::endl;                 \
        ERROR_COUNT++;                                                                 \
    } else {                                                                           \
        std::cout << SUCCESS_TEXT_COLOUR "OK!" NORMAL_TEXT_COLOUR << std::endl;        \
    }

#define ASSERT_ARE_EQUAL(value, expected)                                           \
    {                                                                               \
        std::stringstream stream{};                                                 \
        stream << std::string(expected) << " expected; got " << std::string(value); \
        ASSERT(value == expected, stream.str());                                    \
    }

#define ASSERT_ARE_SAME(value, expected)                          \
    {                                                             \
        void* value_ptr = reinterpret_cast<void*>(&value);        \
        void* expected_ptr = reinterpret_cast<void*>(&expected);  \
        std::stringstream stream{};                               \
        stream << expected_ptr << " expected; got " << value_ptr; \
        ASSERT(value == expected, stream.str());                  \
    }

#define ASSERT_IS_TRUE(value) ASSERT_ARE_EQUAL(value, true);
#define ASSERT_IS_FALSE(value) ASSERT_ARE_EQUAL(value, false);

#define DESCRIBE_CLASS(class_type)                     \
    static const std::string CLASS_NAME = #class_type; \
    template <>                                        \
    TestRunner<class_type>::TestRunner() : _tests()

#define DESCRIBE_TEST(method, situation, expectation) \
    _tests.push_back([]() {});                        \
    _tests[_tests.size() - 1] = [CURRENT_TEST =       \
                                     #method " should " #expectation " when " #situation]()

}  // namespace Tests
}  // namespace SML

#endif
