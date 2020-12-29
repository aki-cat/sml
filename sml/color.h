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

#ifndef SLIPPYS_MATH_LIBRARY_COLOUR_H_
#define SLIPPYS_MATH_LIBRARY_COLOUR_H_

#include <cfloat>
#include <cmath>
#include <sstream>
#include <string>

#define SML_CLAMP_COLOR(c)                   \
    c.r = std::max(0.f, std::min(1.f, c.r)); \
    c.g = std::max(0.f, std::min(1.f, c.g)); \
    c.b = std::max(0.f, std::min(1.f, c.b)); \
    c.a = std::max(0.f, std::min(1.f, c.a))

namespace SML {

class Color {
   public:
    Color() = default;
    Color(int _r, int _g, int _b);
    Color(int _r, int _g, int _b, int _a);
    Color(float _r, float _g, float _b);
    Color(float _r, float _g, float _b, float _a);

    // data
    float r, g, b, a;

    // methods
    const std::string to_string() const;

    // convenient
    static Color white();
    static Color black();
    static Color red();
    static Color green();
    static Color blue();
    static Color invisible();
    static Color gray();
};

// Imutable operators

Color operator*(const float f, const Color& c);

Color operator*(const Color& c, const float f);

Color operator*(const Color& c1, const Color& c2);

Color operator/(const Color& c, const float f);

Color operator/(const Color& c1, const Color& c2);

Color operator+(const Color& c1, const Color& c2);

Color operator-(const Color& c1, const Color& c2);

// Mutable operators

Color& operator*=(Color& c, const float f);

Color& operator/=(Color& c, const float f);

Color& operator*=(Color& c1, const Color& c2);

Color& operator/=(Color& c1, const Color& c2);

Color& operator+=(Color& c1, const Color& c2);

Color& operator-=(Color& c1, const Color& c2);

/*

====================
== IMPLEMENTATION ==
====================

*/

inline Color::Color(int _r, int _g, int _b) {
    r = static_cast<float>(_r) / 0xff;
    g = static_cast<float>(_g) / 0xff;
    b = static_cast<float>(_b) / 0xff;
    a = 1.f;
    SML_CLAMP_COLOR((*this));
}

inline Color::Color(int _r, int _g, int _b, int _a) {
    r = static_cast<float>(_r) / 0xff;
    g = static_cast<float>(_g) / 0xff;
    b = static_cast<float>(_b) / 0xff;
    a = static_cast<float>(_a) / 0xff;
    SML_CLAMP_COLOR((*this));
}

inline Color::Color(float _r, float _g, float _b) : Color(_r, _g, _b, 1.f) {}

inline Color::Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {
    SML_CLAMP_COLOR((*this));
}

// Static members

inline Color Color::white() { return Color(1.f, 1.f, 1.f, 1.f); }

inline Color Color::black() { return Color(0.f, 0.f, 0.f, 1.f); }

inline Color Color::red() { return Color(1.f, 0.f, 0.f, 1.f); }

inline Color Color::green() { return Color(0.f, 1.f, 0.f, 1.f); }

inline Color Color::blue() { return Color(0.f, 0.f, 1.f, 1.f); }

inline Color Color::invisible() { return Color(0.f, 0.f, 0.f, 0.f); }

inline Color Color::gray() { return Color(.5f, .5f, .5f, 1.f); }

// Methods

inline const std::string Color::to_string() const {
    std::stringstream stream;
    char buffer[32];

    stream << "Color #0x";
    std::sprintf(buffer, "%2X", static_cast<uint8_t>(std::round(r * 0xff)));
    stream << buffer;
    std::sprintf(buffer, "%2X", static_cast<uint8_t>(std::round(g * 0xff)));
    stream << buffer;
    std::sprintf(buffer, "%2X", static_cast<uint8_t>(std::round(b * 0xff)));
    stream << buffer;
    std::sprintf(buffer, "%2X", static_cast<uint8_t>(std::round(a * 0xff)));
    stream << buffer;

    return stream.str();
}

// Imutable operators

inline Color operator*(const float f, const Color& c) {
    return Color(f * c.r, f * c.g, f * c.b, f * c.a);
}

inline Color operator*(const Color& c, const float f) {
    return Color(f * c.r, f * c.g, f * c.b, f * c.a);
}

inline Color operator*(const Color& c1, const Color& c2) {
    return Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b, c1.a * c2.a);
}

inline Color operator/(const Color& c, const float f) {
    return Color(c.r / f, c.g / f, c.b / f, c.a / f);
}

inline Color operator/(const Color& c1, const Color& c2) {
    return Color(c1.r / c2.r, c1.g / c2.g, c1.b / c2.b, c1.a / c2.a);
}

inline Color operator+(const Color& c1, const Color& c2) {
    return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a + c2.a);
}

inline Color operator-(const Color& c1, const Color& c2) {
    return Color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b, c1.a - c2.a);
}

// Mutable operators

inline Color& operator*=(Color& c, const float f) {
    c.r *= f;
    c.g *= f;
    c.b *= f;
    c.a *= f;
    SML_CLAMP_COLOR(c);
    return c;
}

inline Color& operator/=(Color& c, const float f) {
    c.r /= f;
    c.g /= f;
    c.b /= f;
    c.a /= f;
    SML_CLAMP_COLOR(c);
    return c;
}

inline Color& operator*=(Color& c1, const Color& c2) {
    c1.r *= c2.r;
    c1.g *= c2.g;
    c1.b *= c2.b;
    c1.a *= c2.a;
    SML_CLAMP_COLOR(c1);
    return c1;
}

inline Color& operator/=(Color& c1, const Color& c2) {
    c1.r /= c2.r;
    c1.g /= c2.g;
    c1.b /= c2.b;
    c1.a /= c2.a;
    SML_CLAMP_COLOR(c1);
    return c1;
}

inline Color& operator+=(Color& c1, const Color& c2) {
    c1.r += c2.r;
    c1.g += c2.g;
    c1.b += c2.b;
    c1.a += c2.a;
    SML_CLAMP_COLOR(c1);
    return c1;
}

inline Color& operator-=(Color& c1, const Color& c2) {
    c1.r -= c2.r;
    c1.g -= c2.g;
    c1.b -= c2.b;
    c1.a -= c2.a;
    SML_CLAMP_COLOR(c1);
    return c1;
}

}  // namespace SML

namespace std {

inline string to_string(const SML::Color& c) { return c.to_string(); }

}  // namespace std

#undef SML_CLAMP_COLOR

#endif
