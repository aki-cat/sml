#include "smltests.h"
#include "vector3.h"

#include <cassert>

namespace SML {
namespace Tests {

void Vec3_TranslationAndAddition_ExpectedResult() {
    {
        const Vec3 a{1, 2, 3};
        const Vec3 b{1, 2, 3};
        const Vec3 a_plus_b = a + b;
        assert(a_plus_b == Vec3(2, 4, 6));
    }

    {
        const Vec3 a{5, 4, 9};
        const Vec3 b{-1, -7, -5};
        const Vec3 a_translated_b = a.translated(b);
        assert(a_translated_b == Vec3(4, -3, 4));
    }

    {
        Vec3 a{5, 4, 9};
        Vec3 b{-1, -7, -5};
        Vec3& c = (a += b);
        ASSERT_ARE_SAME(b, a);
        ASSERT_ARE_EQUAL(c, b);
    }
}

}  // namespace Tests
}  // namespace SML
