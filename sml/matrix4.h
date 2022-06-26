/**
 * Copyright (c) 2022 W. Akira Mizutani
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

#ifndef SLIPPYS_MATH_LIBRARY_MATRIX4_H_
#define SLIPPYS_MATH_LIBRARY_MATRIX4_H_

#include <cstring>
#include <sml/quaternion.h>
#include <sml/transform.h>
#include <sml/vector3.h>

namespace sml {

struct Points16 {
    float f[16];
};

class Mat4 {
   public:
    Mat4();
    Mat4(const Points16& points);

    // transformation methods
    Mat4 translated(const Vec3& v) const;
    Mat4& translate(const Vec3& v);
    Mat4& scale(const float a);
    Mat4 scaled(const float a) const;
    Mat4 rotated(const Vec3& axis, const float angle) const;
    Mat4& rotate(const Vec3& axis, const float angle);
    Mat4 transposed() const;
    Mat4& transpose();

    // misc methods
    std::string to_string() const;
    Mat4& round();
    Mat4& copy(const Mat4& m);

    // useful constant matrices
    static Mat4 identity();
    static Mat4 zero();

    // useful dynamic matrices
    static Mat4 orthogonal_projection(float min_x, float min_y, float max_x, float max_y,
                                      float z_near, float z_far);
    static Mat4 conical_projection(float fov, float aspect, float z_near, float z_far);
    static Mat4 look_at(const Vec3& from, const Vec3& target, const Vec3& up);
    static Mat4 look_at(const Vec3& from, const Vec3& target);

    static const size_t SIZE = 4;
    static const size_t MEM_SIZE = SIZE * SIZE * sizeof(float);

    operator std::string();

    const float* operator[](const size_t n) const;
    float* operator[](const size_t n);

   private:
    float _data[4][4];
};

// Operators

bool operator==(const Mat4& a, const Mat4& b);
bool operator!=(const Mat4& a, const Mat4& b);

Mat4 operator+(const Mat4& a, const Mat4& b);
Mat4 operator-(const Mat4& a, const Mat4& b);
Mat4 operator-(const Mat4& m);

Mat4 operator*(const Mat4& a, const Mat4& b);
Vec3 operator*(const Mat4& m, const Vec3& v);
Mat4 operator*(const Mat4& m, const float a);
Mat4 operator*(const float a, const Mat4& m);

Mat4& operator+=(Mat4& a, const Mat4& b);
Mat4& operator-=(Mat4& a, const Mat4& b);
Mat4& operator*=(Mat4& a, const Mat4& b);
Mat4& operator*=(Mat4& m, const float a);

/*

====================
== IMPLEMENTATION ==
====================

*/

// Constructors

inline Mat4::Mat4() : Mat4({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}) {}

inline Mat4::Mat4(const Points16& points) : _data{} {
    std::memcpy(_data, points.f, Mat4::MEM_SIZE);
}

// Useful static members

inline Mat4 Mat4::identity() {
    static const Mat4 m = Mat4({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
    return m;
}

inline Mat4 Mat4::zero() {
    static const Mat4 m = Mat4({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    return m;
}

// Useful dynamic matrices

inline Mat4 Mat4::orthogonal_projection(float min_x, float min_y, float max_x, float max_y,
                                        float z_near, float z_far) {
    Mat4 m = Mat4::zero();

    m[0][0] = 2.f / (max_x - min_x);
    m[1][1] = 2.f / (max_y - min_y);
    m[2][2] = -2.f / (z_far - z_near);
    m[3][0] = -((max_x + min_x) / (max_x - min_x));
    m[3][1] = -((max_y + min_y) / (max_y - min_y));
    m[3][2] = -((z_far + z_near) / (z_far - z_near));
    m[3][3] = 1.f;

    return m;
}

inline Mat4 Mat4::conical_projection(float fov, float aspect, float z_near, float z_far) {
    float rect_height = 1.f / static_cast<float>(tan(fov * 0.5));
    float rect_width = 1.f / (aspect * static_cast<float>(tan(fov * 0.5)));

    Mat4 m = Mat4::zero();

    m[0][0] = rect_width;
    m[1][1] = rect_height;
    m[2][2] = (-z_near - z_far) / (z_near - z_far);
    m[3][2] = 2.f * z_far * z_near / (z_near - z_far);
    m[2][3] = 1.f;

    return m;
}

inline Mat4 Mat4::look_at(const Vec3& from, const Vec3& target, const Vec3& up) {
    Vec3 zaxis = (target - from).normalized();

    // xaxis = zaxis x up
    Vec3 xaxis = zaxis.cross(up).normalized();

    // yaxis = xaxis x zaxis
    Vec3 yaxis = xaxis.cross(zaxis);

    Mat4 m = Mat4::identity();

    m[0][0] = xaxis.x;
    m[1][0] = xaxis.y;
    m[2][0] = xaxis.z;

    m[0][1] = yaxis.x;
    m[1][1] = yaxis.y;
    m[2][1] = yaxis.z;

    m[0][2] = -zaxis.x;
    m[1][2] = -zaxis.y;
    m[2][2] = -zaxis.z;

    m[3][0] = -xaxis.dot(from);
    m[3][1] = -yaxis.dot(from);
    m[3][2] = -zaxis.dot(from);

    return m;
}

inline Mat4 Mat4::look_at(const Vec3& from, const Vec3& target) {
    return look_at(from, target, Vec3::up());
}

// Tranformation Methods

inline Mat4 Mat4::translated(const Vec3& v) const {
    Mat4 m = Mat4::identity();
    m[3][0] += v.x;
    m[3][1] += v.y;
    m[3][2] += v.z;
    return (*this) * m;
}

inline Mat4& Mat4::translate(const Vec3& v) {
    Mat4 m = Mat4::identity();
    m[3][0] += v.x;
    m[3][1] += v.y;
    m[3][2] += v.z;
    return (*this) *= m;
}

inline Mat4 Mat4::scaled(const float a) const { return (*this) * a; }

inline Mat4& Mat4::scale(const float a) {
    for (size_t x = 0; x < Mat4::SIZE; x++) {
        for (size_t y = 0; y < Mat4::SIZE; y++) {
            _data[x][y] *= a;
        }
    }
    return (*this);
}

inline Mat4 Mat4::rotated(const Vec3& axis, const float angle) const {
    Quat q = Transform::quaternion_from_rotation(axis, angle);
    Mat4 m = Mat4::identity();

    m[0][0] = 1 - 2 * (q.y * q.y + q.z * q.z);
    m[0][1] = 2 * (q.x * q.y - q.z * q.w);
    m[0][2] = 2 * (q.x * q.z + q.y * q.w);

    m[1][0] = 2 * (q.x * q.y + q.z * q.w);
    m[1][1] = 1 - 2 * (q.x * q.x + q.z * q.z);
    m[1][2] = 2 * (q.y * q.z - q.x * q.w);

    m[2][0] = 2 * (q.x * q.z - q.y * q.w);
    m[2][1] = 2 * (q.y * q.z + q.x * q.w);
    m[2][2] = 1 - 2 * (q.x * q.x + q.y * q.y);

    return (*this) * m.round();
}

inline Mat4& Mat4::rotate(const Vec3& axis, const float angle) {
    Mat4 m = Mat4::identity().rotated(axis, angle);
    return (*this) *= m.round();
}

inline Mat4 Mat4::transposed() const {
    Mat4 m{};

    m.copy(*this);
    m.transpose();

    return m;
}

inline Mat4& Mat4::transpose() {
    float buffer[16] = {_data[0][0], _data[0][1], _data[0][2], _data[0][3],  // force format
                        _data[1][0], _data[1][1], _data[1][2], _data[1][3],
                        _data[2][0], _data[2][1], _data[3][2], _data[2][3],
                        _data[3][0], _data[3][1], _data[4][2], _data[3][3]};
    std::memcpy(_data, buffer, Mat4::MEM_SIZE);
    return (*this);
}

// Misc Methods

inline Mat4& Mat4::round() {
    for (size_t x = 0; x < Mat4::SIZE; x++) {
        for (size_t y = 0; y < Mat4::SIZE; y++) {
            if (std::fabs(_data[x][y]) <= FLT_EPSILON) {
                _data[x][y] = 0;
            }
        }
    }
    return (*this);
}

inline Mat4& Mat4::copy(const Mat4& m) {
    std::memcpy(_data, m._data, Mat4::MEM_SIZE);
    return (*this);
}

inline std::string Mat4::to_string() const {
    std::stringstream stream;
    stream << "Mat4 {\n";

    for (size_t y = 0; y < Mat4::SIZE; y++) {
        stream << "      { ";
        for (size_t x = 0; x < Mat4::SIZE; x++) {
            char buffer[64];
            std::snprintf(buffer, 64, "%+.2f", _data[x][y]);
            stream << buffer << " ";
        }
        stream << "}\n";
    }
    stream << "}\n";

    return stream.str();
}

// Conversion operators

inline Mat4::operator std::string() { return to_string(); }

inline const float* Mat4::operator[](const size_t n) const { return _data[n]; }

inline float* Mat4::operator[](const size_t n) { return _data[n]; }

// Imutable operators

inline bool operator==(const Mat4& a, const Mat4& b) {
    for (size_t x = 0; x < Mat4::SIZE; x++) {
        for (size_t y = 0; y < Mat4::SIZE; y++) {
            if (std::fabs(a[x][y] - b[x][y]) > FLT_EPSILON) {
                return false;
            }
        }
    }
    return true;
}

inline bool operator!=(const Mat4& a, const Mat4& b) {
    for (size_t x = 0; x < Mat4::SIZE; x++) {
        for (size_t y = 0; y < Mat4::SIZE; y++) {
            if (std::fabs(a[x][y] - b[x][y]) > FLT_EPSILON) {
                return true;
            }
        }
    }
    return false;
}

inline Mat4 operator+(const Mat4& a, const Mat4& b) {
    Mat4 m{};
    for (size_t x = 0; x < Mat4::SIZE; x++) {
        for (size_t y = 0; y < Mat4::SIZE; y++) {
            m[x][y] = a[x][y] + b[x][y];
        }
    }
    return m;
}

inline Mat4 operator-(const Mat4& a, const Mat4& b) {
    Mat4 m{};
    for (size_t x = 0; x < Mat4::SIZE; x++) {
        for (size_t y = 0; y < Mat4::SIZE; y++) {
            m[x][y] = a[x][y] - b[x][y];
        }
    }
    return m;
}

inline Mat4 operator*(const Mat4& a, const Mat4& b) {
    Mat4 m;

    m[0][0] = a[0][0] * b[0][0] + a[1][0] * b[0][1] + a[2][0] * b[0][2] + a[3][0] * b[0][3];
    m[1][0] = a[0][0] * b[1][0] + a[1][0] * b[1][1] + a[2][0] * b[1][2] + a[3][0] * b[1][3];
    m[2][0] = a[0][0] * b[2][0] + a[1][0] * b[2][1] + a[2][0] * b[2][2] + a[3][0] * b[2][3];
    m[3][0] = a[0][0] * b[3][0] + a[1][0] * b[3][1] + a[2][0] * b[3][2] + a[3][0] * b[3][3];

    m[0][1] = a[0][1] * b[0][0] + a[1][1] * b[0][1] + a[2][1] * b[0][2] + a[3][1] * b[0][3];
    m[1][1] = a[0][1] * b[1][0] + a[1][1] * b[1][1] + a[2][1] * b[1][2] + a[3][1] * b[1][3];
    m[2][1] = a[0][1] * b[2][0] + a[1][1] * b[2][1] + a[2][1] * b[2][2] + a[3][1] * b[2][3];
    m[3][1] = a[0][1] * b[3][0] + a[1][1] * b[3][1] + a[2][1] * b[3][2] + a[3][1] * b[3][3];

    m[0][2] = a[0][2] * b[0][0] + a[1][2] * b[0][1] + a[2][2] * b[0][2] + a[3][2] * b[0][3];
    m[1][2] = a[0][2] * b[1][0] + a[1][2] * b[1][1] + a[2][2] * b[1][2] + a[3][2] * b[1][3];
    m[2][2] = a[0][2] * b[2][0] + a[1][2] * b[2][1] + a[2][2] * b[2][2] + a[3][2] * b[2][3];
    m[3][2] = a[0][2] * b[3][0] + a[1][2] * b[3][1] + a[2][2] * b[3][2] + a[3][2] * b[3][3];

    m[0][3] = a[0][3] * b[0][0] + a[1][3] * b[0][1] + a[2][3] * b[0][2] + a[3][3] * b[0][3];
    m[1][3] = a[0][3] * b[1][0] + a[1][3] * b[1][1] + a[2][3] * b[1][2] + a[3][3] * b[1][3];
    m[2][3] = a[0][3] * b[2][0] + a[1][3] * b[2][1] + a[2][3] * b[2][2] + a[3][3] * b[2][3];
    m[3][3] = a[0][3] * b[3][0] + a[1][3] * b[3][1] + a[2][3] * b[3][2] + a[3][3] * b[3][3];

    return m;
}

// We always assume vector is susceptible to translations (w = 1)
inline Vec3 operator*(const Mat4& m, const Vec3& v) {
    return Vec3(m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0],
                m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1],
                m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2]);
}

inline Mat4 operator*(const Mat4& m, const float a) {
    Mat4 n{};
    for (size_t x = 0; x < Mat4::SIZE; x++) {
        for (size_t y = 0; y < Mat4::SIZE; y++) {
            n[x][y] = m[x][y] * a;
        }
    }
    return n;
}

inline Mat4 operator*(const float a, const Mat4& m) {
    Mat4 n{};
    for (size_t x = 0; x < Mat4::SIZE; x++) {
        for (size_t y = 0; y < Mat4::SIZE; y++) {
            n[x][y] = m[x][y] * a;
        }
    }
    return n;
}

inline Mat4 operator-(const Mat4& m) {
    Mat4 n{};
    for (size_t x = 0; x < Mat4::SIZE; x++) {
        for (size_t y = 0; y < Mat4::SIZE; y++) {
            n[x][y] = -m[x][y];
        }
    }
    return n;
}

// Mutable operators

inline Mat4& operator+=(Mat4& a, const Mat4& b) {
    for (size_t x = 0; x < Mat4::SIZE; x++) {
        for (size_t y = 0; y < Mat4::SIZE; y++) {
            a[x][y] += b[x][y];
        }
    }
    return a;
}

inline Mat4& operator-=(Mat4& a, const Mat4& b) {
    for (size_t x = 0; x < Mat4::SIZE; x++) {
        for (size_t y = 0; y < Mat4::SIZE; y++) {
            a[x][y] -= b[x][y];
        }
    }
    return a;
}

inline Mat4& operator*=(Mat4& a, const Mat4& b) {
    Mat4 result = a * b;
    std::memcpy(&a, &result, Mat4::MEM_SIZE);
    return a;
}

inline Mat4& operator*=(Mat4& m, const float a) {
    for (size_t x = 0; x < Mat4::SIZE; x++) {
        for (size_t y = 0; y < Mat4::SIZE; y++) {
            m[x][y] *= a;
        }
    }
    return m;
}

}  // namespace sml

namespace std {

inline string to_string(const sml::Mat4& m) { return m.to_string(); }

}  // namespace std

#endif
