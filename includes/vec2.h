#ifndef VEC2_H
#define VEC2_H

#include <cmath>

template <typename T>
struct vector {
    T x;
    T y;

    vector() = default;
    vector(T _x, T _y) {x = _x; y = _y;};

    T length(){
        return sqrt(x*x + y*y);
    }

    vector<T> normalized(){
        T l = length();
        vector<T> result(x / l, y / l);
        return result;
    }

    bool operator==(const vector &other) const {
        return other.x == x && other.y == y;
    }

    bool operator!=(const vector &other) const {
        return !(other.x == x && other.y == y);
    }

    vector<T> operator+(const vector<T> &other) const {
        return {other.x + x, other.y + y};
    }

    vector<T> operator*(const float factor) const {
        return {(T) (x * factor), (T)(y * factor)};
    }
};

template <typename T>
float distance(const vector<T> &v1, vector<T> &v2) {
    float x = (v2.x - v1.x);
    float y = (v2.y - v1.y);
    return sqrt(x*x + y*y);
}

using vec2 = vector<float>;
using vec2i = vector<int>;

#endif
