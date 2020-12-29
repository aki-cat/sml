/**
 * Copyright (c) 2020 W. Akira Mizutani
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
