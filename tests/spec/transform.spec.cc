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
