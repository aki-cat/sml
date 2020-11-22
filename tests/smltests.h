#ifndef SLIPPYS_MATH_LIBRARY_TESTS_H
#define SLIPPYS_MATH_LIBRARY_TESTS_H

#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace std {

const string& to_string(const string& s) { return s; }
string to_string(const bool& value) { return value ? "true" : "false"; }

}  // namespace std

namespace SML {
namespace Tests {

static uint32_t ERROR_COUNT = 0;

template <typename T>
constexpr const char* CLASS_NAME;

template <typename T>
class TestRunner {
   public:
    TestRunner();

    static void run() {
        const TestRunner<T> runner = TestRunner<T>();
        for (auto const test : runner._tests) {
            test();
        }
        std::cout << std::endl;
    }

   private:
    using class_t = T;
    std::vector<std::function<void(void)>> _tests;
};

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

#define PRINT_TEST_SUCCESS() std::cout << SUCCESS_TEXT_COLOUR "OK!" NORMAL_TEXT_COLOUR << std::endl
#define PRINT_TEST_FAILURE(error_msg) std::cerr << ASSERTION_FAIL_MESSAGE << error_msg << std::endl
#define PRINT_TEST_DESCRIPTION() \
    std::cout << "\t" << CLASS_NAME<class_t> << NORMAL_TEXT_COLOUR << "::" << CURRENT_TEST << " "

#define ASSERT(expr, error_msg)        \
    PRINT_TEST_DESCRIPTION();          \
    if (!(expr)) {                     \
        ERROR_COUNT++;                 \
        PRINT_TEST_FAILURE(error_msg); \
    } else {                           \
        PRINT_TEST_SUCCESS();          \
    }

#define ASSERT_ARE_EQUAL(value, expected)                                                 \
    {                                                                                     \
        std::stringstream stream{};                                                       \
        stream << std::to_string(expected) << " expected; got " << std::to_string(value); \
        ASSERT(value == expected, stream.str());                                          \
    }

#define ASSERT_ARE_SAME(value, expected)                          \
    {                                                             \
        void* value_ptr = reinterpret_cast<void*>(&value);        \
        void* expected_ptr = reinterpret_cast<void*>(&expected);  \
        std::stringstream stream{};                               \
        stream << expected_ptr << " expected; got " << value_ptr; \
        ASSERT(value == expected, stream.str());                  \
    }

#define ASSERT_IS_TRUE(value) ASSERT_ARE_EQUAL((value), true);
#define ASSERT_IS_FALSE(value) ASSERT_ARE_EQUAL((value), false);

#define ASSERT_ARRAYS_ARE_EQUAL(value, expected, range_start, range_length)              \
    {                                                                                    \
        PRINT_TEST_DESCRIPTION();                                                        \
        std::stringstream stream{};                                                      \
        stream << std::endl;                                                             \
        bool success = true;                                                             \
        for (int range_index = range_start; range_index < range_length; range_index++) { \
            if (!(value[range_index] == expected[range_index])) {                        \
                success = false;                                                         \
                stream << "\t\t- " << expected[range_index] << " expected at index #"    \
                       << range_index << "; got " << value[range_index] << std::endl;    \
            }                                                                            \
        }                                                                                \
        if (success) {                                                                   \
            PRINT_TEST_SUCCESS();                                                        \
        } else {                                                                         \
            ERROR_COUNT++;                                                               \
            PRINT_TEST_FAILURE(stream.str());                                            \
        };                                                                               \
    }

#define DESCRIBE_CLASS(class_type)                              \
    template <>                                                 \
    constexpr const char* CLASS_NAME<class_type> = #class_type; \
    template <>                                                 \
    TestRunner<class_type>::TestRunner() : _tests()

#define DESCRIBE_TEST(method, situation, expectation)                            \
    _tests.push_back([]() {});                                                   \
    _tests[_tests.size() - 1] = [CURRENT_TEST = NORMAL_TEXT_COLOUR_BOLD #method  \
                                 "()" NORMAL_TEXT_COLOUR " should " #expectation \
                                 " when " #situation]()

}  // namespace Tests
}  // namespace SML

#endif
