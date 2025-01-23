#include "Mat.h"

template class Mat<int>;
template class Mat<double>;

//constructors
template <typename T>
Mat<T>::Mat(int rows, int cols) : rows(rows), cols(cols), data(new T[rows * cols]{ 0 }) {
    if (rows == cols) {
        for (int i = 0; i < rows; i++) {
            data[i * cols + i] = 1;
        }
    }

}

template <typename T>
Mat<T>::Mat(int rows, int cols, T default_val) : rows(rows), cols(cols), data(new T[rows * cols]{ default_val }) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[cols * i + j] = default_val;
        }
    }
}

template <typename T>
Mat<T>::Mat(const Mat<T>& other) : rows(other.rows), cols(other.cols), data(new T[other.rows * other.cols]{ 0 }) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            this->data[i * cols + j] = other.data[i * cols + j];
        }
    }

}

template<typename T>
Mat<T>::Mat(const Mat<T>&& other) : rows(other.rows), cols(other.cols), data(new T[other.rows * other.cols]{ 0 })
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            this->data[i * cols + j] = other.data[i * cols + j];
        }
    }
}

//operators
template <typename T>
Mat<T> Mat<T>::operator*(const float scalar) const {
    Mat<T> output(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            output.data[i * cols + j] = (T)(data[i * cols + j] * scalar);
        }
    }
    return output;
}

template <typename T>
bool Mat<T>::operator!=(const Mat<T>& other) {
    if (this == &other)
        return false;

    for (int i = 0; i < other.rows * other.cols; i++) {
        if (data[i] != other.data[i])
            return true;
    }

    return false;
}

template <typename T>
T& Mat<T>::operator[](int i) {
    if (i >= rows * cols)
        throw std::runtime_error("carray out of bound");
    return data[i];
}

template<typename T>
Mat<double> Mat<T>::inverse()
{
    if(this->rows != 3 || this->cols != 3)
        throw std::runtime_error("cannot calculate inverse");
    Mat<T> CoFactor(3,3);
    // 0 1 2
    // 3 4 5
    // 6 7 8
    //calculate cofactor
    CoFactor.data[0] = this->data[4] * this->data[8] - this->data[5] * this->data[7];
    CoFactor.data[1] = (this->data[3] * this->data[8] - this->data[5] * this->data[6]) * -1;
    CoFactor.data[2] = this->data[3] * this->data[7] - this->data[4] * this->data[6];
    CoFactor.data[3] = (this->data[1] * this->data[8] - this->data[2] * this->data[7]) * -1;
    CoFactor.data[4] = this->data[0] * this->data[8] - this->data[2] * this->data[6];
    CoFactor.data[5] = (this->data[0] * this->data[7] - this->data[1] * this->data[6]) * -1;
    CoFactor.data[6] = this->data[1] * this->data[5] - this->data[2] * this->data[4];
    CoFactor.data[7] = (this->data[0] * this->data[5] - this->data[2] * this->data[3]) * -1;
    CoFactor.data[8] = this->data[0] * this->data[4] - this->data[1] * this->data[3];

    double determinant = (this->data[0] * CoFactor.data[0]) - (this->data[1] * (CoFactor.data[1] * -1)) + (this->data[2] * CoFactor.data[2]); 

    Mat<double> inverse(3, 3);
    inverse.data[0] = CoFactor.data[0] * (1.0 / determinant);
    inverse.data[1] = CoFactor.data[3] * (1.0 / determinant);
    inverse.data[2] = CoFactor.data[6] * (1.0 / determinant);
    inverse.data[3] = CoFactor.data[1] * (1.0 / determinant);
    inverse.data[4] = CoFactor.data[4] * (1.0 / determinant);
    inverse.data[5] = CoFactor.data[7] * (1.0 / determinant);
    inverse.data[6] = CoFactor.data[2] * (1.0 / determinant);
    inverse.data[7] = CoFactor.data[5] * (1.0 / determinant);
    inverse.data[8] = CoFactor.data[8] * (1.0 / determinant);
    

    return inverse;
}