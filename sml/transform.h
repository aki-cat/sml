#ifndef SARGASSO_ENGINE_COMMON_MATH_TRANSFORM_H
#define SARGASSO_ENGINE_COMMON_MATH_TRANSFORM_H

#include <sml/matrix4.h>
#include <sml/quaternion.h>
#include <sml/vector3.h>

namespace SML {

class Transform {
   public:
    Transform() = delete;

    static Vec3& translate(Vec3& a, const Vec3& b);
    static Vec3 translated(const Vec3& a, const Quat& b);

    static Vec3& scale(Vec3& v, const float a);
    static Vec3 scaled(const Vec3& v, const float a);

    static Vec3& rotate(Vec3& v, const Quat& q);
    static Vec3 rotated(const Vec3& v, const Quat& q);

    // Helper static constructors
    static Quat quaternion_from_vector(const float w, const Vec3& v);
    static Quat quaternion_from_vector(const Vec3& v);
    static Quat quaternion_from_rotation(const Vec3& axis, const float angle);
    static Vec3 vector_from_quaternion(const Quat& q);
};

// Operators between non-native math types

Quat operator*(const Quat& a, const Vec3& b);
Quat operator*(const Vec3& a, const Quat& b);

// IMPLEMENTATION

inline Vec3& translate(Vec3& a, const Vec3& b) { return a += b; }

inline Vec3 translated(const Vec3& a, const Vec3& b) { return a + b; }

inline Vec3& scale(Vec3& v, const float a) { return v *= a; }

inline Vec3 scaled(const Vec3& v, const float a) { return v * a; }

inline Vec3& Transform::rotate(Vec3& v, const Quat& q) {
    const Vec3& qv = vector_from_quaternion(q);
    return v += (2 * (qv ^ ((qv ^ v) + q.w * v)));
}

inline Vec3 Transform::rotated(const Vec3& v, const Quat& q) {
    const Vec3& qv = vector_from_quaternion(q);
    return v + 2 * (qv ^ ((qv ^ v) + q.w * v));
}

inline Quat Transform::quaternion_from_vector(const float w, const Vec3& v) {
    return Quat(w, v.x, v.y, v.z);
}

inline Quat Transform::quaternion_from_vector(const Vec3& v) { return Quat(0.0f, v.x, v.y, v.z); }

inline Quat Transform::quaternion_from_rotation(const Vec3& axis, const float angle) {
    float sine = static_cast<float>(sin(angle / 2));
    float cosine = static_cast<float>(cos(angle / 2));
    const Vec3 vector_component = sine * axis.normalized();
    return Quat(cosine, vector_component.x, vector_component.y, vector_component.z);
}

inline Vec3 Transform::vector_from_quaternion(const Quat& q) { return Vec3(q.x, q.y, q.z); }

}  // namespace SML

#endif
