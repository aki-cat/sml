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
#include <sml/matrix4.h>
#include <type_traits>

using sml::Mat4;
using sml::Vec3;

DESCRIBE_CLASS(Mat4) {
    DESCRIBE_TEST(operator[], SimpleMatrix, ReturnExpectedContents) {
        Mat4 mat({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        const float* raw_result = reinterpret_cast<const float*>(&mat);
        const float expected[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        ASSERT_ARRAYS_ARE_EQUAL(raw_result, expected, 0, 16);
    };

    DESCRIBE_TEST(reinterpret_cast<float*>, SimpleMatrix, ReturnExpectedContents) {
        Mat4 mat({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        const float* raw_result = reinterpret_cast<const float*>(&mat);
        const float expected[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        ASSERT_ARRAYS_ARE_EQUAL(raw_result, expected, 0, 16);
    };

    DESCRIBE_TEST(operator*, MulitipliedByIdentity, ReturnSelfEquivalent) {
        Mat4 mat({2, 8, 3, 4, 5, 7, 2, 1, 4, 7, 8, 1, 3, 4, 2, 5});
        Mat4 result = mat * Mat4::identity();
        const float* raw_result = reinterpret_cast<const float*>(&result);
        const float expected[16] = {2, 8, 3, 4, 5, 7, 2, 1, 4, 7, 8, 1, 3, 4, 2, 5};
        ASSERT_ARRAYS_ARE_EQUAL(raw_result, expected, 0, 16);
    };

    DESCRIBE_TEST(operator*, MulitipliedBySomeMatrix, ReturnExpectedResult) {
        Mat4 mat({2, 8, 3, 4, 5, 7, 2, 1, 4, 7, 8, 1, 3, 4, 2, 5});
        Mat4 result = mat * Mat4({4, 3, 7, 5, 1, 7, 4, 8, 4, 0, 2, 1, 5, 7, 9, 3});
        const float* raw_result = reinterpret_cast<const float*>(&result);
        const float expected[16] = {66.f, 122.f, 84.f, 51.f, 77.f, 117.f, 65.f,  55.f,
                                    19.f, 50.f,  30.f, 23.f, 90.f, 164.f, 107.f, 51.f};
        ASSERT_ARRAYS_ARE_EQUAL(raw_result, expected, 0, 16);
    };

    DESCRIBE_TEST(operator*, MultipliedToVec3, ReturnExpectedResult) {
        Mat4 mat({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        Vec3 result = mat * Vec3(17, 18, 19);
        const float* raw_result = reinterpret_cast<const float*>(&(result));
        const float expected[] = {291.f, 346.f, 401.f};
        ASSERT_ARRAYS_ARE_EQUAL(raw_result, expected, 0, 3);
    };

    DESCRIBE_TEST(rotated, MultipliedToVec3, ReturnExpectedResult) {
        Mat4 rotation = Mat4::identity().rotated(Vec3::y_axis(), M_PI / 6);
        Vec3 result = rotation * Vec3(-2, 1, -1);
        Vec3 expected = Vec3(.5f - std::sqrt(3), 1, -1 - std::sqrt(3) / 2.f);
        ASSERT_ARE_EQUAL(result, expected);
    };

    DESCRIBE_TEST(orthogonal_projection, TranslatedVertex, ReturnExpectedResult) {
        Vec3 vertex = Vec3(-2, 2, 0);
        Mat4 model = Mat4::identity().rotated(Vec3::z_axis(), M_PI_2);
        Mat4 projection = Mat4::orthogonal_projection(-10, -5, 10, 5, -100, 100);

        vertex = projection * model * vertex;

        ASSERT_ARE_EQUAL(vertex, Vec3(.2, .4, 0));
    };

    DESCRIBE_TEST(orthogonal_projection, RotatedVertex, ReturnExpectedResult) {
        Vec3 vertex = Vec3(1, 0, 0);
        Vec3 results[8];

        const float sqrt_2 = std::sqrt(2.f) / 2.f;

        const Vec3 expected[] = {
            Vec3(+.1f, 0, 0), Vec3(+sqrt_2 * .1f, +sqrt_2 * .2f, 0),
            Vec3(0, +.2f, 0), Vec3(-sqrt_2 * .1f, +sqrt_2 * .2f, 0),
            Vec3(-.1f, 0, 0), Vec3(-sqrt_2 * .1f, -sqrt_2 * .2f, 0),
            Vec3(0, -.2f, 0), Vec3(+sqrt_2 * .1f, -sqrt_2 * .2f, 0),
        };

        for (size_t i = 0; i < 8; i++) {
            double angle = -(static_cast<double>(i) * M_PI_4);
            Mat4 model = Mat4::identity().rotated(Vec3::z_axis(), angle);
            Mat4 projection = Mat4::orthogonal_projection(-10, -5, 10, 5, -100, 100);
            results[i] = projection * model * vertex;
        }

        ASSERT_ARRAYS_ARE_EQUAL(results, expected, 0, 8);
    };

    DESCRIBE_TEST(std::is_standard_layout, CheckedByCompiler, BeStandardLayout) {
        ASSERT_IS_TRUE(std::is_standard_layout<Mat4>::value);
    };
}
