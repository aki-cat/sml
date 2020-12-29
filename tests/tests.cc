
#include "spec/color.spec.cc"
#include "spec/matrix4.spec.cc"
#include "spec/quaternion.spec.cc"
#include "spec/transform.spec.cc"
#include "spec/vector3.spec.cc"

#include <btl.h>
#include <iostream>

static std::string red_text(const std::string& text) {
    return std::string("\033[91m" + text + "\033[0m");
}

static std::string green_text(const std::string& text) {
    return std::string("\033[92m" + text + "\033[0m");
}

int main() {
    std::cout << std::endl << "Running tests..." << std::endl << std::endl;

    btl::TestRunner<sml::Color>::run();
    btl::TestRunner<sml::Vec3>::run();
    btl::TestRunner<sml::Quat>::run();
    btl::TestRunner<sml::Mat4>::run();
    btl::TestRunner<sml::Transform>::run();

    if (btl::has_errors()) {
        std::cerr << red_text("One or more tests failed!") << std::endl << std::endl;
        return -1;
    }

    std::cout << green_text("Tests were successful!") << std::endl << std::endl;
    return 0;
}
