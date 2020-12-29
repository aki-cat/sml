/**
 * Copyright (c) 2020 W. Akira Mizutani
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <btl.h>
#include <sml/quaternion.h>
#include <type_traits>

using sml::Quat;

DESCRIBE_CLASS(Quat) {
    DESCRIBE_TEST(operator+, AddingTwoQuaternions, ReturnExpectedResult) {
        const Quat a{1, 2, 3, 4};
        const Quat b{1, 2, 3, 4};
        Quat a_plus_b = a + b;
        ASSERT_ARE_EQUAL(a_plus_b, Quat({2, 4, 6, 8}));
    };

    DESCRIBE_TEST(operator+=, AddingTwoQuaternions, ReturnExpectedResult) {
        Quat a{5, 4, 9, -1};
        a += Quat({2, 3, 4, 6});
        ASSERT_ARE_EQUAL(a, Quat({7, 7, 13, 5}));
    };

    DESCRIBE_TEST(operator+=, AddingTwoQuaternions, ReturnExpectedReference) {
        Quat a{5, 4, 9, 2};
        Quat& c = (a += Quat({2, 3, 4, 1}));
        ASSERT_ARE_SAME(a, c);
    };

    DESCRIBE_TEST(added, SimpleSum, ReturnExpectedResult) {
        Quat a{5, 4, 9, 2};
        Quat b{1, 1, 1, 3};
        Quat a_translated_b = a.added(b);
        ASSERT_ARE_EQUAL(a_translated_b, Quat({6, 5, 10, 5}));
    };

    DESCRIBE_TEST(to_string, ConvertingVectorToString, ReturnExpectedResult) {
        Quat a{1, 2, 3, 4};
        ASSERT_ARE_EQUAL(std::to_string(a), std::string("Quat(1, 2, 3, 4)"));
    };

    DESCRIBE_TEST(reinterpret_cast<float*>, SimpleVector, ReturnExpectedContents) {
        Quat v{1, 2, 3, 4};
        float* cast_v = reinterpret_cast<float*>(&v);
        float expected[] = {1, 2, 3, 4};
        ASSERT_ARRAYS_ARE_EQUAL(cast_v, expected, 0, 4);
    };

    DESCRIBE_TEST(std::is_standard_layout, CheckedByCompiler, BeStandardLayout) {
        ASSERT_IS_TRUE(std::is_standard_layout<Quat>::value);
    };
}
