#include "smltests.h"
#include "vector3.h"

namespace SML {
namespace Tests {

DESCRIBE_CLASS(Vec3) {
    DESCRIBE_TEST(operator_plus, AddingTwoVectors, ReturnExpectedResult) {
        Vec3 a{1, 2, 3};
        Vec3 b{1, 2, 3};
        Vec3 a_plus_b = a + b;
        ASSERT_ARE_EQUAL(a_plus_b, Vec3(2, 4, 6));
    };

    DESCRIBE_TEST(translated, SimpleTranslation, ReturnExpectedResult) {
        Vec3 a{5, 4, 9};
        Vec3 b{1, 1, 1};
        Vec3 a_translated_b = a.translated(b);
        ASSERT_ARE_EQUAL(a_translated_b, Vec3(6, 5, 10));
    };

    DESCRIBE_TEST(operator_plus_equal, AddingTwoVectors, ReturnExpectedResultAndReference) {
        Vec3 a{5, 4, 9};
        Vec3 b{-1, -7, -5};
        Vec3& c = (a += b);
        ASSERT_ARE_SAME(a, c);
        ASSERT_ARE_EQUAL(a, Vec3(4, -3, 4));
    };
}

}  // namespace Tests
}  // namespace SML
