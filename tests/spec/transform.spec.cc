
#include "smltests.h"

#include <sml/quaternion.h>
#include <sml/transform.h>
#include <sml/vector3.h>

namespace SML {
namespace Tests {

DESCRIBE_CLASS(Transform) {
    DESCRIBE_TEST(rotated, RotatedBy90Degrees, ReturnExpectedResult) {
        const Vec3 v({1, 1, 1});
        const Quat q =
            Transform::quaternion_from_rotation(Vec3::y_axis(), static_cast<float>(M_PI) / 2);

        const Vec3 result = Transform::rotated(v, q);
        const Vec3 expected{1, 1, -1};

        // We check with this wide a range because of float point error
        ASSERT_ARE_EQUAL(result, expected);
    };
}

}  // namespace Tests
}  // namespace SML
