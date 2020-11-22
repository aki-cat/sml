
#include "smltests.h"

#include <sml/matrix4.h>

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
}

}  // namespace Tests
}  // namespace SML
