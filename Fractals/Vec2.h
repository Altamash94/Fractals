#pragma once
#include <iostream>
#include <ostream>
#include "Mat.h"

template<typename T>
class Vec2 {
public:
    T x;
    T y;
    Vec2(T x, T y);
    
    Vec2<T> operator-(const Vec2<T>& other) const;
    Vec2<T> operator+(const Vec2<T>& other) const;
    Vec2<T> operator*(double mul) const;
    bool operator<(const Vec2<T>& other) const;
    friend std::ostream& operator << (std::ostream& out, const Vec2<T>& vec)
    {
        out << "(" << vec.x << ", " << vec.y << ")";
        return out;
    }
    
    Vec2<double> Normalize(int width, int height);
    Vec2<int> DeNormalize(int width, int height);
    Vec2<T> Transform(Mat<double> m_transform, int width, int height);
};
