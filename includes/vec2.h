#ifndef VEC2_H
#define VEC2_H

#include <cmath>

template <typename T>
struct vector {
    T x;
    T y;

    vector(T _x, T _y) {x = _x; y = _y;};

    T length(){
        return sqrt(x*x + y*y);
    }

    vector<T> normalized(){
        T l = length();
        vector<T> result(x / l, y / l);
        return result;
    }
};

using vec2 = vector<float>;
using vec2i = vector<int>;

#endif
