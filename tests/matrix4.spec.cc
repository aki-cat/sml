
#include "matrix4.h"
#include "smltests.h"

namespace SML {
namespace Tests {

DESCRIBE_CLASS(Mat4) {
    DESCRIBE_TEST(operator[], SimpleMatrix, ReturnExpectedContents) {
        Mat4 mat({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        float expected[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        ASSERT_ARRAYS_ARE_EQUAL(mat, expected, 0, 16);
    };
}

}  // namespace Tests
}  // namespace SML
