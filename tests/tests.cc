
#include "matrix4.spec.cc"
#include "vector3.spec.cc"

#include <iostream>

using namespace SML;
using namespace SML::Tests;

int main() {
    // Vec3 tests

    std::cout << std::endl << "Running tests..." << std::endl << std::endl;

    TestRunner<Vec3>::run();
    TestRunner<Mat4>::run();

    if (ERROR_COUNT > 0) {
        return -1;
    }

    return 0;
}
