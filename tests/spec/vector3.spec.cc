#include <btl.h>
#include <sml/vector3.h>
#include <type_traits>

using sml::Vec3;

DESCRIBE_CLASS(Vec3) {
    DESCRIBE_TEST(operator+, AddingTwoVectors, ReturnExpectedResult) {
        const Vec3 a{1, 2, 3};
        const Vec3 b{1, 2, 3};
        Vec3 a_plus_b = a + b;
        ASSERT_ARE_EQUAL(a_plus_b, Vec3({2, 4, 6}));
    };

    DESCRIBE_TEST(operator+=, AddingTwoVectors, ReturnExpectedResult) {
        Vec3 a{5, 4, 9};
        a += Vec3({2, 3, 4});
        ASSERT_ARE_EQUAL(a, Vec3({7, 7, 13}));
    };

    DESCRIBE_TEST(operator+=, AddingTwoVectors, ReturnExpectedReference) {
        Vec3 a{5, 4, 9};
        Vec3& c = (a += Vec3({2, 3, 4}));
        ASSERT_ARE_SAME(a, c);
    };

    DESCRIBE_TEST(translated, SimpleTranslation, ReturnExpectedResult) {
        Vec3 a{5, 4, 9};
        Vec3 b{1, 1, 1};
        Vec3 a_translated_b = a.translated(b);
        ASSERT_ARE_EQUAL(a_translated_b, Vec3({6, 5, 10}));
    };

    DESCRIBE_TEST(dot, SimpleDotProduct, ReturnExpectedResult) {
        Vec3 a{2, 1, 0};
        Vec3 b{1, -2, 0};
        float a_dot_b = a.dot(b);
        ASSERT_ARE_EQUAL(a_dot_b, 0.f);
    };

    DESCRIBE_TEST(to_string, ConvertingVectorToString, ReturnExpectedResult) {
        Vec3 a{1, 2, 3};
        ASSERT_ARE_EQUAL(std::to_string(a), std::string("Vec3(+1.000, +2.000, +3.000)"));
    };

    DESCRIBE_TEST(reinterpret_cast<float*>, SimpleVector, ReturnExpectedContents) {
        Vec3 v{1, 2, 3};
        float* cast_v = reinterpret_cast<float*>(&v);
        float expected[3] = {1, 2, 3};
        ASSERT_ARRAYS_ARE_EQUAL(cast_v, expected, 0, 3);
    };

    DESCRIBE_TEST(std::is_standard_layout, CheckedByCompiler, BeStandardLayout) {
        ASSERT_IS_TRUE(std::is_standard_layout<Vec3>::value);
    };
}
