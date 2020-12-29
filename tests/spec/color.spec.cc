#include <btl.h>
#include <sml/color.h>

using sml::Color;

DESCRIBE_CLASS(Color) {
    DESCRIBE_TEST(to_string, ConvertingColorToString, ReturnExpectedResult) {
        Color c(0x80, 0x80, 0x80);
        ASSERT_ARE_EQUAL(std::to_string(c), std::string("Color #0x808080FF"));
    };

    DESCRIBE_TEST(Color, PassingOutOfRangeValues, ClampColorValues) {
        Color c(-10, 1024, 333, -1000);
        float* cast_c = reinterpret_cast<float*>(&c);
        float expected[] = {0.f, 1.f, 1.f, 0.f};
        ASSERT_ARRAYS_ARE_EQUAL(cast_c, expected, 0, 3);
    };

    DESCRIBE_TEST(reinterpret_cast<float*>, SimpleColor, ReturnExpectedContents) {
        Color c(.1f, .2f, .3f);
        float* cast_c = reinterpret_cast<float*>(&c);
        float expected[] = {.1f, .2f, .3f, 1.f};
        ASSERT_ARRAYS_ARE_EQUAL(cast_c, expected, 0, 4);
    };

    DESCRIBE_TEST(std::is_standard_layout, CheckedByCompiler, BeStandardLayout) {
        ASSERT_IS_TRUE(std::is_standard_layout<Color>::value);
    };
}
