/**
 * Copyright (c) 2022 W. Akira Mizutani
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
#include <sml/color.h>

using sml::Color;

DESCRIBE_CLASS(Color) {
    DESCRIBE_TEST(to_string, ConvertingColorToString, ReturnExpectedResult) {
        Color c(0x80, 0x80, 0x80);
        ASSERT_ARE_EQUAL(std::to_string(c), std::string("Color #0x808080FF"));
    };

    DESCRIBE_TEST(Color, PassingOutOfRangeValues, ClampColorValues) {
        Color c(-10, 1024, 333, -1000);
        float* cast_c = reinterpret_cast<float*>(&c);
        float expected[] = {0.f, 1.f, 1.f, 0.f};
        ASSERT_ARRAYS_ARE_EQUAL(cast_c, expected, 0, 3);
    };

    DESCRIBE_TEST(reinterpret_cast<float*>, SimpleColor, ReturnExpectedContents) {
        Color c(.1f, .2f, .3f);
        float* cast_c = reinterpret_cast<float*>(&c);
        float expected[] = {.1f, .2f, .3f, 1.f};
        ASSERT_ARRAYS_ARE_EQUAL(cast_c, expected, 0, 4);
    };

    DESCRIBE_TEST(std::is_standard_layout, CheckedByCompiler, BeStandardLayout) {
        ASSERT_IS_TRUE(std::is_standard_layout<Color>::value);
    };
}
