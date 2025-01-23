#include "Vec2.h"

template class Vec2<int>;
template class Vec2<double>;

//constructors
template <typename T>
Vec2<T>::Vec2(T x, T y) : x(x), y(y) {}


//operators
template <typename T>
Vec2<T> Vec2<T>::operator-(const Vec2<T>& other) const {
    return Vec2<T>(x - other.x, y - other.y);
}

template <typename T>
Vec2<T> Vec2<T>::operator+(const Vec2<T>& other) const {
    return Vec2<T>(x + other.x, y + other.y);
}

template <typename T>
Vec2<T> Vec2<T>::operator*(double mul) const {
    return Vec2<T>((T)(x * mul), (T)(y * mul));
}

template <typename T>
bool Vec2<T>::operator<(const Vec2<T>& other) const {
    double a = sqrt(x * x + y * y);
    double b = sqrt(other.x * other.x + other.y * other.y);
    return a < b;
}

//functions
template <typename T>
Vec2<double> Vec2<T>::Normalize(int width, int height) {
    double x = (this->x * 2.0 - width) / height;
    double y = (this->y * 2.0 - height) / height;
    return Vec2<double>(x, y);
}

template <typename T>
Vec2<int> Vec2<T>::DeNormalize(int width, int height) {
    double i = ((x + 1.0) * height) / 2;
    double j = ((y + 1.0) * height) / 2;

    return Vec2<int>((int)std::round(i), (int)std::round(j));
}

template<typename T>
Vec2<T> Vec2<T>::Transform(Mat<double> m_transform, int width, int height)
{
    Mat<double> mat(3, 1);
    mat[0] = this->x;
    mat[1] = this->y;
    mat[2] = 1;
    mat = m_transform * mat;
    
    return Vec2<T>((T)mat[0], (T)mat[1]);
}