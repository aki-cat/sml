#ifndef SLIPPYS_MATH_LIBRARY_VECTOR3_SPEC_H
#define SLIPPYS_MATH_LIBRARY_VECTOR3_SPEC_H

#include "smltests.h"
#include "vector3.h"

#include <cassert>
#include <iostream>

namespace SML {
namespace Tests {

void Vec3_AddOperation_ExpectedResult() {
    const Vec3 v{1, 2, 3};
    const Vec3 u{1, 2, 3};

    const Vec3 t = v + u;

    assert(t == Vec3(2, 4, 6));
}

}  // namespace Tests
}  // namespace SML

#endif
