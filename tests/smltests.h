#ifndef SLIPPYS_MATH_LIBRARY_TESTS_H
#define SLIPPYS_MATH_LIBRARY_TESTS_H

#define LOCATION_TEXT_COLOUR "\033[94;1m"
#define FAILURE_TEXT_COLOUR "\033[91m"
#define NORMAL_TEXT_COLOUR "\033[0m"
#define NORMAL_TEXT_COLOUR_BOLD "\033[0;1m"

#define S1(x) #x
#define S2(x) S1(x)
#define SELF(x) x
#define LOCATION_MESSAGE LOCATION_TEXT_COLOUR __FILE__ "(" S2(__LINE__) "):" NORMAL_TEXT_COLOUR
#define ASSERTION_FAIL_MESSAGE \
    LOCATION_MESSAGE FAILURE_TEXT_COLOUR " Assertion failed! " NORMAL_TEXT_COLOUR

#include <cstdint>
#include <cstdio>
#include <iostream>

namespace SML {
namespace Tests {

static uint32_t ERROR_COUNT = 0;
static std::string CURRENT_CLASS = "<NoClass>";

}  // namespace Tests
}  // namespace SML

using namespace SML::Tests;

#define ASSERT(expr, error_msg)                                        \
    if (!(expr)) {                                                     \
        std::cerr << ASSERTION_FAIL_MESSAGE << error_msg << std::endl; \
        ERROR_COUNT++;                                                 \
    }

#define ASSERT_ARE_EQUAL(value, expected)                                           \
    {                                                                               \
        std::stringstream stream{};                                                 \
        stream << std::string(value) << " expected; got " << std::string(expected); \
        ASSERT(a == b, stream.str());                                               \
    }

#define ASSERT_ARE_SAME(value, expected)                          \
    {                                                             \
        void* value_ptr = reinterpret_cast<void*>(&value);        \
        void* expected_ptr = reinterpret_cast<void*>(&expected);  \
        std::stringstream stream{};                               \
        stream << value_ptr << " expected; got " << expected_ptr; \
        ASSERT(value == expected, stream.str());                  \
    }

// Test definition

#define SML_TEST(method, case, expectation) \
    void SELF(method) SELF(_) SELF(case) SELF(_) SELF(expectation)

#endif
