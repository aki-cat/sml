
#include "vector3.spec.cc"

#include <iostream>

using namespace SML;

int main() {
    // Vec3 tests

    std::cout << std::endl << "Running tests..." << std::endl << std::endl;

    Tests::Vec3_TranslationAndAddition_ExpectedResult();

    if (SML::Tests::ERROR_COUNT > 0) {
        return -1;
    }

    return 0;
}
