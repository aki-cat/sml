#include "smltests.h"

#include <sml/vector3.h>

namespace SML {
namespace Tests {

DESCRIBE_CLASS(Quat) {
    DESCRIBE_TEST(operator+, AddingTwoVectors, ReturnExpectedResult) {
        const Quat a{1, 2, 3, 4};
        const Quat b{1, 2, 3, 4};
        Quat a_plus_b = a + b;
        ASSERT_ARE_EQUAL(a_plus_b, Quat({2, 4, 6, 8}));
    };

    DESCRIBE_TEST(operator+=, AddingTwoVectors, ReturnExpectedResult) {
        Quat a{5, 4, 9, -1};
        a += Quat({2, 3, 4, 6});
        ASSERT_ARE_EQUAL(a, Quat({7, 7, 13, 5}));
    };

    DESCRIBE_TEST(operator+=, AddingTwoVectors, ReturnExpectedReference) {
        Quat a{5, 4, 9, 2};
        Quat& c = (a += Quat({2, 3, 4, 1}));
        ASSERT_ARE_SAME(a, c);
    };

    DESCRIBE_TEST(added, SimpleTranslation, ReturnExpectedResult) {
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

    DESCRIBE_TEST(std::is_trivial, CheckedByCompiler, BeTrivial) {
        ASSERT_IS_FALSE(std::is_trivial<Quat>::value);
    };

    DESCRIBE_TEST(std::is_standard_layout, CheckedByCompiler, BeStandardLayout) {
        ASSERT_IS_TRUE(std::is_standard_layout<Quat>::value);
    };

    DESCRIBE_TEST(std::is_pod, CheckedByCompiler, BePOD) {
        ASSERT_IS_FALSE(std::is_pod<Quat>::value);
    };
}

}  // namespace Tests
}  // namespace SML
