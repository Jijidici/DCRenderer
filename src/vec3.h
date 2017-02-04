#pragma once

#include <math.h>
#include <stdlib.h>
#include <iostream>

namespace dc
{

template <class T>
class vec3 {
public:
    vec3() {}
    vec3(T v) { e[0] = v; e[1] = v; e[2] = v; }
    vec3(T e0, T e1, T e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
    inline T x() const { return e[0]; }
    inline T y() const { return e[1]; }
    inline T z() const { return e[2]; }
    inline T r() const { return e[0]; }
    inline T g() const { return e[1]; }
    inline T b() const { return e[2]; }

    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    inline T operator[](int i) const { return e[i]; }
    inline T& operator[](int i) { return e[i]; }

    inline vec3& operator+=(const vec3& other) { e[0] += other.e[0]; e[1] += other.e[1]; e[2] += other.e[2]; return *this; }
    inline vec3& operator-=(const vec3& other) { e[0] -= other.e[0]; e[1] -= other.e[1]; e[2] -= other.e[2]; return *this; }
    inline vec3& operator*=(const vec3& other) { e[0] *= other.e[0]; e[1] *= other.e[1]; e[2] *= other.e[2]; return *this; }
    inline vec3& operator/=(const vec3& other) { e[0] /= other.e[0]; e[1] /= other.e[1]; e[2] /= other.e[2]; return *this; }
    inline vec3& operator*=(const T t) { e[0] *= t; e[1] *= t; e[2] *= t; return *this; }
    inline vec3& operator/=(const T t) { e[0] /= t; e[1] /= t; e[2] /= t; return *this; }

    inline T length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
    inline T squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    inline void normalized() {
        T k = ((T)1) / length();
        e[0] *= k; e[1] *= k; e[2] *= k;
    }

protected:
    T e[3];
};

// math functions
template <class T>
inline T dot(const vec3<T>& v1, const vec3<T>& v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

template <class T>
inline vec3<T> cross(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>((v1[1] * v2[2]) - (v1[2] * v2[1]),
                 -((v1[0] * v2[2]) - (v1[2] * v2[0])),
                   (v1[0] * v2[1]) - (v1[1] * v2[0]));
}

template <class T>
inline vec3<T> normalize(const vec3<T>& v) {
    vec3<T> res = v;
    res.normalized();
    return res;
}

// stream functions
template <class T>
inline std::istream& operator>>(std::istream& is, vec3<T>& v) {
    is >> v[0] >> v[1] >> v[2];
    return is;
}

template <class T>
inline std::ostream& operator<<(std::ostream& os, vec3<T>& v) {
    os << v[0] << " " << v[1] << " " << v[2];
    return os;
}

// vec (op) vec
template <class T>
inline vec3<T> operator+(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

template <class T>
inline vec3<T> operator-(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

template <class T>
inline vec3<T> operator*(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

template <class T>
inline vec3<T> operator/(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}

// vec (op) float
template <class T>
inline vec3<T> operator+(const vec3<T>& v, T t) {
    return vec3<T>(v[0] + t, v[1] + t, v[2] + t);
}

template <class T>
inline vec3<T> operator-(const vec3<T>& v, T t) {
    return vec3<T>(v[0] - t, v[1] - t, v[2] - t);
}

template <class T>
inline vec3<T> operator*(const vec3<T>& v, T t) {
    return vec3<T>(v[0] * t, v[1] * t, v[2] * t);
}

template <class T>
inline vec3<T> operator/(const vec3<T>& v, T t) {
    return vec3<T>(v[0] / t, v[1] / t, v[2] / t);
}

// float (op) vec
template <class T>
inline vec3<T> operator+(T t, const vec3<T>& v) {
    return vec3<T>(t + v[0], t + v[1], t + v[2]);
}

template <class T>
inline vec3<T> operator-(T t, const vec3<T>& v) {
    return vec3<T>(t - v[0], t - v[1], t - v[2]);
}

template <class T>
inline vec3<T> operator*(T t, const vec3<T>& v) {
    return vec3<T>(t * v[0], t * v[1], t * v[2]);
}

// typedefs
typedef vec3<float> v3f;
typedef vec3<float> color;
typedef vec3<double> v3d;
typedef vec3<int> v3i;

} // dc