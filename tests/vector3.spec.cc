#include "smltests.h"
#include "vector3.h"

namespace SML {
namespace Tests {

DEFINE_CLASS_TESTS(Vec3) {
    DEFINE_TEST(operator_plus, SumOfTwoVectors, ExpectedResult) {
        Vec3 a{1, 2, 3};
        Vec3 b{1, 2, 3};
        Vec3 a_plus_b = a + b;
        ASSERT_ARE_EQUAL(a_plus_b, Vec3(2, 4, 6));
    };

    DEFINE_TEST(translated, SimpleTranslation, ExpectedResult) {
        Vec3 a{5, 4, 9};
        Vec3 b{1, 1, 1};
        Vec3 a_translated_b = a.translated(b);
        ASSERT_ARE_EQUAL(a_translated_b, Vec3(6, 5, 10));
    };

    DEFINE_TEST(operator_plus_equal, SumOfTwoVectors, ExpectedResultAndReference) {
        Vec3 a{5, 4, 9};
        Vec3 b{-1, -7, -5};
        Vec3& c = (a += b);
        ASSERT_ARE_SAME(a, c);
        ASSERT_ARE_EQUAL(a, Vec3(4, -3, 4));
    };
}

}  // namespace Tests
}  // namespace SML
