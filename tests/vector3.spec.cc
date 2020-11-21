#include "smltests.h"
#include "vector3.h"

namespace SML {
namespace Tests {

DESCRIBE_CLASS(Vec3) {
    DESCRIBE_TEST(operator+, AddingTwoVectors, ReturnExpectedResult) {
        const Vec3 a{1, 2, 3};
        const Vec3 b{1, 2, 3};
        Vec3 a_plus_b = a + b;
        ASSERT_ARE_EQUAL(a_plus_b, Vec3(2, 4, 6));
    };

    DESCRIBE_TEST(operator+=, AddingTwoVectors, ReturnExpectedResult) {
        Vec3 a{5, 4, 9};
        a += Vec3{2, 3, 4};
        ASSERT_ARE_EQUAL(a, Vec3(7, 7, 13));
    };

    DESCRIBE_TEST(operator+=, AddingTwoVectors, ReturnExpectedReference) {
        Vec3 a{5, 4, 9};
        Vec3& c = (a += Vec3{2, 3, 4});
        ASSERT_ARE_SAME(a, c);
    };

    DESCRIBE_TEST(translated, SimpleTranslation, ReturnExpectedResult) {
        Vec3 a{5, 4, 9};
        Vec3 b{1, 1, 1};
        Vec3 a_translated_b = a.translated(b);
        ASSERT_ARE_EQUAL(a_translated_b, Vec3(6, 5, 10));
    };

    DESCRIBE_TEST(to_string, ConvertingVectorToString, ReturnExpectedResult) {
        Vec3 a{1, 2, 3};
        ASSERT_ARE_EQUAL(std::to_string(a), std::string("Vec3(1, 2, 3)"));
    };
}

}  // namespace Tests
}  // namespace SML
