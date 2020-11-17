#ifndef SARGASSO_ENGINE_COMMON_MATH_QUATERNION_H
#define SARGASSO_ENGINE_COMMON_MATH_QUATERNION_H

#include <cfloat>
#include <cmath>
#include <sstream>
#include <string>

#include "points.h"

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

namespace SargassoEngine {
namespace Common {
namespace Math {

class Quat {
 public:
  Quat(float _w, float _x, float _y, float _z);
  Quat();

  // data
  float &w, &x, &y, &z;

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

 private:
  Points4 _points;
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

inline Quat::Quat(float _w, float _x, float _y, float _z)
    : w{_points.p[0]},
      x{_points.p[1]},
      y{_points.p[2]},
      z{_points.p[3]},
      _points{} {
  _points.p[0] = _w;
  _points.p[1] = _x;
  _points.p[2] = _y;
  _points.p[3] = _z;
}

inline Quat::Quat() : Quat(1.0f, 0.0f, 0.0f, 0.0f) {}

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

inline float Quat::norm() const {
  return static_cast<float>(sqrt(w * w + x * x + y * y + z * z));
}

inline float Quat::norm_squared() const {
  return w * w + x * x + y * y + z * z;
}

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

}  // namespace Math
}  // namespace Common
}  // namespace SargassoEngine

#endif
