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

#ifndef SLIPPYS_MATH_LIBRARY_VECTOR3_H_
#define SLIPPYS_MATH_LIBRARY_VECTOR3_H_

#include <cfloat>
#include <cmath>
#include <sstream>
#include <string>

namespace SML {

class Vec3 {
   public:
    Vec3(float _x, float _y, float _z);
    Vec3();

    // data
    float x, y, z;

    // methods
    const std::string to_string() const;

    float dot(const Vec3& v) const;
    Vec3 cross(const Vec3& v) const;

    Vec3 normalized() const;
    Vec3& normalize();

    Vec3 clamped(const float s) const;
    Vec3& clamp(const float s);

    float length() const;
    float length_squared() const;

    Vec3 translated(const Vec3& v) const;
    Vec3& translate(const Vec3& v);

    Vec3& rotate(const Vec3& axis, const double angle);
    Vec3 rotated(const Vec3& axis, const double angle) const;

    Vec3 scaled(const float s) const;
    Vec3& scale(const float s);

    // convenient
    static Vec3 zero();
    static Vec3 up();
    static Vec3 down();
    static Vec3 front();
    static Vec3 back();
    static Vec3 left();
    static Vec3 right();

    // convenient axes
    static Vec3 x_axis();
    static Vec3 y_axis();
    static Vec3 z_axis();
};

// Imutable operators

bool operator==(const Vec3& a, const Vec3& b);

bool operator!=(const Vec3& a, const Vec3& b);

Vec3 operator*(const float a, const Vec3& v);

Vec3 operator*(const Vec3& v, const float a);

Vec3 operator/(const Vec3& v, const float a);

float operator*(const Vec3& a, const Vec3& b);

Vec3 operator^(const Vec3& a, const Vec3& b);

Vec3 operator+(const Vec3& a, const Vec3& b);

Vec3 operator-(const Vec3& a, const Vec3& b);

Vec3 operator-(const Vec3& v);

// Mutable operators

Vec3& operator*=(Vec3& v, const float a);

Vec3& operator/=(Vec3& v, const float a);

Vec3& operator+=(Vec3& a, const Vec3& b);

Vec3& operator-=(Vec3& a, const Vec3& b);

/*

====================
== IMPLEMENTATION ==
====================

*/

inline Vec3::Vec3(float _x, float _y, float _z) : x{_x}, y{_y}, z{_z} {}

inline Vec3::Vec3() : Vec3(0.0f, 0.0f, 0.0f) {}

// Static members

inline Vec3 Vec3::zero() {
    static const Vec3 v = Vec3();
    return v;
}

inline Vec3 Vec3::up() {
    static const Vec3 v = Vec3(0, 1, 0);
    return v;
}

inline Vec3 Vec3::down() {
    static const Vec3 v = Vec3(0, -1, 0);
    return v;
}

inline Vec3 Vec3::front() {
    static const Vec3 v = Vec3(0, 0, -1);
    return v;
}

inline Vec3 Vec3::back() {
    static const Vec3 v = Vec3(0, 0, 1);
    return v;
}

inline Vec3 Vec3::left() {
    static const Vec3 v = Vec3(-1, 0, 0);
    return v;
}

inline Vec3 Vec3::right() {
    static const Vec3 v = Vec3(1, 0, 0);
    return v;
}

inline Vec3 Vec3::x_axis() {
    static const Vec3 v = Vec3(1.0f, 0.0f, 0.0f);
    return v;
}

inline Vec3 Vec3::y_axis() {
    static const Vec3 v = Vec3(0.0f, 1.0f, 0.0f);
    return v;
}

inline Vec3 Vec3::z_axis() {
    static const Vec3 v = Vec3(0.0f, 0.0f, 1.0f);
    return v;
}

// Methods

inline const std::string Vec3::to_string() const {
    std::stringstream stream;
    char buffer[32];

    stream << "Vec3(";
    std::sprintf(buffer, "%+.3f", x);
    stream << buffer << ", ";
    std::sprintf(buffer, "%+.3f", y);
    stream << buffer << ", ";
    std::sprintf(buffer, "%+.3f", z);
    stream << buffer << ")";

    return stream.str();
}

/*
Dot product
ux * vx + uy * vy + uz * vz
*/
inline float Vec3::dot(const Vec3& v) const { return (x * v.x) + (y * v.y) + (z * v.z); }

/*
Cross product
|  i  j  k   |
|  a1 a2 a3  |
|  b1 b2 b3  |
*/
inline Vec3 Vec3::cross(const Vec3& v) const {
    return Vec3((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
}

inline Vec3 Vec3::normalized() const {
    const float normalization = 1.0f / length();
    return Vec3(x * normalization, y * normalization, z * normalization);
}

inline Vec3& Vec3::normalize() {
    const float normalization = 1.0f / length();
    x *= normalization;
    y *= normalization;
    z *= normalization;
    return *this;
}

inline Vec3 Vec3::clamped(const float s) const {
    Vec3 normal = normalized();
    return normal.scaled(s);
}

inline Vec3& Vec3::clamp(const float s) {
    normalize();
    return scale(s);
}

inline float Vec3::length() const { return static_cast<float>(sqrt(length_squared())); }

inline float Vec3::length_squared() const { return dot(*this); }

inline Vec3 Vec3::translated(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }

inline Vec3& Vec3::translate(const Vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

inline Vec3 Vec3::rotated(const Vec3& axis, const double angle) const {
    const float sine = static_cast<float>(sin(angle));
    const float cosine = static_cast<float>(cos(angle));
    const Vec3 normal = axis.normalized();
    const Vec3& v = (*this);
    return (1 - cosine) * dot(normal) * normal + cosine * v + sine * normal.cross(v);
}

inline Vec3& Vec3::rotate(const Vec3& axis, const double angle) {
    const Vec3 result = rotated(axis, angle);
    x = result.x;
    y = result.y;
    z = result.z;
    return *this;
}

inline Vec3 Vec3::scaled(const float s) const { return Vec3(x * s, y * s, z * s); }

inline Vec3& Vec3::scale(const float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

// Imutable operators

inline bool operator==(const Vec3& a, const Vec3& b) {
    return fabs(a.x - b.x) <= FLT_EPSILON && fabs(a.y - b.y) <= FLT_EPSILON &&
           fabs(a.z - b.z) <= FLT_EPSILON;
}

inline bool operator!=(const Vec3& a, const Vec3& b) {
    return fabs(a.x - b.x) > FLT_EPSILON || fabs(a.y - b.y) > FLT_EPSILON ||
           fabs(a.z - b.z) > FLT_EPSILON;
}

inline Vec3 operator*(const float a, const Vec3& v) { return Vec3(v.x * a, v.y * a, v.z * a); }

inline Vec3 operator*(const Vec3& v, const float a) { return Vec3(v.x * a, v.y * a, v.z * a); }

inline Vec3 operator/(const Vec3& v, const float a) {
    const float factor = 1 / a;
    return Vec3(v.x * factor, v.y * factor, v.z * factor);
}

inline Vec3 operator+(const Vec3& a, const Vec3& b) {
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vec3 operator-(const Vec3& a, const Vec3& b) {
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Vec3 operator-(const Vec3& v) { return Vec3(-v.x, -v.y, -v.z); }

inline float operator*(const Vec3& a, const Vec3& b) { return a.dot(b); }

inline Vec3 operator^(const Vec3& a, const Vec3& b) { return a.cross(b); }

// Mutable operators

inline Vec3& operator*=(Vec3& v, const float a) {
    v.x *= a;
    v.y *= a;
    v.z *= a;
    return v;
}

inline Vec3& operator/=(Vec3& v, const float a) {
    v.x /= a;
    v.y /= a;
    v.z /= a;
    return v;
}

inline Vec3& operator+=(Vec3& a, const Vec3& b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

inline Vec3& operator-=(Vec3& a, const Vec3& b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

}  // namespace SML

namespace std {

inline string to_string(const SML::Vec3& v) { return v.to_string(); }

}  // namespace std

#endif
