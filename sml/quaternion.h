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

#ifndef SLIPPYS_MATH_LIBRARY_QUATERNION_H_
#define SLIPPYS_MATH_LIBRARY_QUATERNION_H_

#include <cfloat>
#include <cmath>
#include <sstream>
#include <string>

/*

e ^ (theta * normal_quat) = cos(theta) + sin(theta) * normal_quat

sin(theta) * normal_quat = sin(theta) * (0, normal_x, normal_y, normal_z)

v3_rotated_quat = e ^ (theta/2 * normal_quat) * v3_quat * e ^ (-theta/2 *
normal_quat)

e ^ (theta/2 * normal_quat) =
    (cos(theta/2), sin(theta/2) * normal_x, sin(theta/2) * normal_y,
sin(theta/2) * normal_z)

e ^ (-theta/2 * normal_quat) =
    (cos(theta/2), -sin(theta/2) * normal_x, -sin(theta/2) * normal_y,
-sin(theta/2) * normal_z)

*/

namespace sml {

class Quat {
   public:
    Quat();
    Quat(float _w, float _x, float _y, float _z);

    // data
    float w, x, y, z;

    // methods
    const std::string to_string() const;

    Quat& add(const Quat& q);
    Quat added(const Quat& q) const;

    Quat& scale(const float a);
    Quat scaled(const float a) const;

    Quat multiplied(const Quat& q) const;

    Quat& normalize();
    Quat normalized() const;

    Quat& conjugate();
    Quat conjugated() const;

    float norm() const;
    float norm_squared() const;

    // convenient
    static Quat identity();
    static Quat zero();
    static Quat i();
    static Quat j();
    static Quat k();

    // conversions
    operator std::string();
};

// Imutable operators

bool operator==(const Quat& a, const Quat& b);
bool operator!=(const Quat& a, const Quat& b);

Quat operator*(const float a, const Quat& q);
Quat operator*(const Quat& q, const float a);
Quat operator/(const Quat& q, const float a);

Quat operator*(const Quat& a, const Quat& b);
Quat operator+(const Quat& a, const Quat& b);
Quat operator-(const Quat& a, const Quat& b);

Quat operator-(const Quat& q);

// Mutable operators

Quat& operator*=(Quat& q, const float a);
Quat& operator/=(Quat& q, const float a);
Quat& operator+=(Quat& a, const Quat& b);
Quat& operator-=(Quat& a, const Quat& b);

/*

====================
== IMPLEMENTATION ==
====================

*/

inline Quat::Quat() : Quat(1.0f, 0.0f, 0.0f, 0.0f) {}

inline Quat::Quat(float _w, float _x, float _y, float _z) : w{_w}, x{_x}, y{_y}, z{_z} {}

// Static members

inline Quat Quat::identity() {
    static const Quat q = Quat(1.0f, 0.0f, 0.0f, 0.0f);
    return q;
}

inline Quat Quat::zero() {
    static const Quat q = Quat(0.0f, 0.0f, 0.0f, 0.0f);
    return q;
}

inline Quat Quat::i() {
    static const Quat q = Quat(0.0f, 1.0f, 0.0f, 0.0f);
    return q;
}

inline Quat Quat::j() {
    static const Quat q = Quat(0.0f, 0.0f, 1.0f, 0.0f);
    return q;
}

inline Quat Quat::k() {
    static const Quat q = Quat(0.0f, 0.0f, 0.0f, 1.0f);
    return q;
}

// Methods

inline const std::string Quat::to_string() const {
    std::ostringstream stream{};
    stream << "Quat(" << w << ", " << x << ", " << y << ", " << z << ")";
    return stream.str();
}

inline Quat& Quat::add(const Quat& q) { return (*this) += q; }
inline Quat Quat::added(const Quat& q) const { return (*this) + q; }

inline Quat& Quat::scale(const float a) { return (*this) *= a; }
inline Quat Quat::scaled(const float a) const { return (*this) * a; }

inline Quat Quat::multiplied(const Quat& q) const { return (*this) * q; }

inline Quat& Quat::normalize() {
    float factor = 1 / norm();
    w *= factor;
    x *= factor;
    y *= factor;
    z *= factor;
    return (*this);
}

inline Quat Quat::normalized() const {
    float factor = 1 / norm();
    return Quat(w * factor, x * factor, y * factor, z * factor);
}

inline Quat& Quat::conjugate() {
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

inline Quat Quat::conjugated() const { return Quat(w, -x, -y, -z); }

inline float Quat::norm() const { return static_cast<float>(sqrt(w * w + x * x + y * y + z * z)); }

inline float Quat::norm_squared() const { return w * w + x * x + y * y + z * z; }

// Conversion operators

inline Quat::operator std::string() { return to_string(); }

// Imutable operators

inline bool operator==(const Quat& a, const Quat& b) {
    return fabs(a.w - b.w) <= FLT_EPSILON && fabs(a.x - b.x) <= FLT_EPSILON &&
           fabs(a.y - b.y) <= FLT_EPSILON && fabs(a.z - b.z) <= FLT_EPSILON;
}

inline bool operator!=(const Quat& a, const Quat& b) {
    return fabs(a.w - b.w) > FLT_EPSILON || fabs(a.x - b.x) > FLT_EPSILON ||
           fabs(a.y - b.y) > FLT_EPSILON || fabs(a.z - b.z) > FLT_EPSILON;
}

inline Quat operator*(const float a, const Quat& q) {
    return Quat(a * q.w, a * q.x, a * q.y, a * q.z);
}

inline Quat operator*(const Quat& q, const float a) {
    return Quat(a * q.w, a * q.x, a * q.y, a * q.z);
}

inline Quat operator/(const Quat& q, const float a) {
    const float factor = 1 / a;
    return Quat(factor * q.w, factor * q.x, factor * q.y, factor * q.z);
}

/*
Quaternion multiplication
a | w -x -y -z |   b | w |
  | x  w -z -y |     | x |
  | y  z  w -x | x   | y |
  | z  y  x  w |     | z |

*/
inline Quat operator*(const Quat& a, const Quat& b) {
    return Quat(a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
                a.x * b.w + a.w * b.x - a.z * b.y - a.y * b.z,
                a.y * b.w + a.z * b.x + a.w * b.y - a.x * b.z,
                a.z * b.w + a.y * b.x + a.x * b.y + a.w * b.z);
}

inline Quat operator+(const Quat& a, const Quat& b) {
    return Quat(a.w + b.w, a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Quat operator-(const Quat& a, const Quat& b) {
    return Quat(a.w - b.w, a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Quat operator-(const Quat& q) { return Quat(-q.w, -q.x, -q.y, -q.z); }

// Mutable operators

inline Quat& operator*=(Quat& q, const float a) {
    q.w *= a;
    q.x *= a;
    q.y *= a;
    q.z *= a;
    return q;
}

inline Quat& operator/=(Quat& q, const float a) {
    q.w /= a;
    q.x /= a;
    q.y /= a;
    q.z /= a;
    return q;
}

inline Quat& operator+=(Quat& a, const Quat& b) {
    a.w += b.w;
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

inline Quat& operator-=(Quat& a, const Quat& b) {
    a.w -= b.w;
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

}  // namespace sml

namespace std {

inline string to_string(const sml::Quat& q) { return q.to_string(); }

}  // namespace std

#endif
