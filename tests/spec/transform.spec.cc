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
#include <sml/quaternion.h>
#include <sml/transform.h>
#include <sml/vector3.h>
#include <type_traits>

using sml::Quat;
using sml::Transform;
using sml::Vec3;

DESCRIBE_CLASS(Transform) {
    DESCRIBE_TEST(rotated, RotatedBy45Degrees, ReturnExpectedAngularResult) {
        const Vec3 v({1, 1, 1});
        const Quat q =
            Transform::quaternion_from_rotation(Vec3::y_axis(), static_cast<float>(M_PI_4));

        const Vec3 result = Transform::rotated(v, q);
        const double expected_cosine = std::sqrt(2.0);
        const double resulting_angle = result.x / result.y;

        // We check with this wide a range because of float point error
        ASSERT_ARE_EQUAL(resulting_angle, expected_cosine);
    };

    DESCRIBE_TEST(rotated, RotatedBy45Degrees, ReturnExpectedLengthResult) {
        const Vec3 v({3, 4, 0});
        const Quat q =
            Transform::quaternion_from_rotation(Vec3::z_axis(), static_cast<float>(M_PI_4));

        const Vec3 result = Transform::rotated(v, q);
        const float expected = 5.f;

        // We check with this wide a range because of float point error
        ASSERT_ARE_EQUAL(result.length(), expected);
    };
}
