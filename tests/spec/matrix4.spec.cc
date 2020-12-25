
#include "smltests.h"

#include <sml/matrix4.h>
#include <type_traits>

namespace SML {
namespace Tests {

DESCRIBE_CLASS(Mat4) {
    DESCRIBE_TEST(operator[], SimpleMatrix, ReturnExpectedContents) {
        Mat4 mat({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        float expected[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        ASSERT_ARRAYS_ARE_EQUAL(mat, expected, 0, 16);
    };

    DESCRIBE_TEST(reinterpret_cast<float*>, SimpleMatrix, ReturnExpectedContents) {
        Mat4 mat({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        float* cast_mat = reinterpret_cast<float*>(&mat);
        float expected[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        ASSERT_ARRAYS_ARE_EQUAL(cast_mat, expected, 0, 16);
    };

    DESCRIBE_TEST(operator*, MulitipliedByIdentity, ReturnSelfEquivalent) {
        Mat4 mat({2, 8, 3, 4, 5, 7, 2, 1, 4, 7, 8, 1, 3, 4, 2, 5});
        Mat4 result = mat * Mat4::identity();
        float expected[16] = {2, 8, 3, 4, 5, 7, 2, 1, 4, 7, 8, 1, 3, 4, 2, 5};
        ASSERT_ARRAYS_ARE_EQUAL(result, expected, 0, 16);
    };

    DESCRIBE_TEST(operator*, MulitipliedBySomeMatrix, ReturnExpectedResult) {
        Mat4 mat({2, 8, 3, 4, 5, 7, 2, 1, 4, 7, 8, 1, 3, 4, 2, 5});
        Mat4 result = mat * Mat4({4, 3, 7, 5, 1, 7, 4, 8, 4, 0, 2, 1, 5, 7, 9, 3});
        float expected[16] = {48, 90, 88, 89, 40, 71, 76, 86, 60, 68, 81, 87, 49, 72, 86, 64};
        ASSERT_ARRAYS_ARE_EQUAL(result, expected, 0, 16);
    };

    DESCRIBE_TEST(operator*, MultipliedToVec3, ReturnExpectedResult) {
        Mat4 mat({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        Vec3 result = mat * Vec3(17, 18, 19);
        float* raw_result = reinterpret_cast<float*>(&(result));
        float expected[] = {114.f, 334.f, 554.f};
        ASSERT_ARRAYS_ARE_EQUAL(raw_result, expected, 0, 3);
    };

    DESCRIBE_TEST(orthogonal_projection, TranslatedVertex, ReturnExpectedResult) {
        Vec3 vertex = Vec3(1, 1, 0);
        Mat4 model = Mat4::identity().translated(Vec3(1, 1, 0));
        Mat4 projection = Mat4::orthogonal_projection(-5, -5, 5, 5, -100, 100);

        vertex = projection * model * vertex;

        ASSERT_ARE_EQUAL(vertex, Vec3(.4, .4, 0));
    };

    DESCRIBE_TEST(std::is_trivial, CheckedByCompiler, BeTrivial) {
        ASSERT_IS_FALSE(std::is_trivial<Mat4>::value);
    };

    DESCRIBE_TEST(std::is_standard_layout, CheckedByCompiler, BeStandardLayout) {
        ASSERT_IS_TRUE(std::is_standard_layout<Mat4>::value);
    };

    DESCRIBE_TEST(std::is_pod, CheckedByCompiler, BePOD) {
        ASSERT_IS_FALSE(std::is_pod<Mat4>::value);
    };
}

}  // namespace Tests
}  // namespace SML
