#pragma once
#include <iostream>
#include <ostream>

template <typename T>
class Mat {
public:
    int rows;
    int cols;
    std::unique_ptr<T[]> data{ nullptr };
    Mat(int rows, int cols);
    Mat(int rows, int cols, T default_val);
    Mat(const Mat<T>& other);
    Mat(const Mat<T>&& other);

    template<typename U>
    Mat<T> operator*(const Mat<U>& operand2) const;
    Mat<T> operator*(const float scalar) const;
    T& operator[](int i);
    bool operator!=(const Mat<T>& other);
    Mat<T>& operator=(const Mat<T>& other);
    
    template<typename U>
    Mat<T>& operator=(const Mat<U>& other);
    
    template<typename U>
    Mat<T>& operator=(const Mat<U> &&other);
    
    friend std::ostream& operator<<(std::ostream& out, const Mat<T>& mat)
    {
        for (int i = 0; i < mat.rows; i++) {
            for (int j = 0; j < mat.cols; j++) {
                out << mat.data[mat.cols * i + j] << " ";
            }
            out << std::endl;
        }
        return out;
    }

    Mat<double> inverse();
};

template<typename T>
template<typename U>
Mat<T> Mat<T>::operator*(const Mat<U>& operand2) const {
    if (cols != operand2.rows)
        throw std::runtime_error("cannot multiply the matrices");
    Mat<T> output(rows, operand2.cols, 0);
    //std::cout << "operand1\n" << *this << std::endl;
    //std::cout << "operand2\n"<< operand2 << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < output.cols; j++) {
            for (int k = 0; k < cols; k++) {
                output.data[(output.cols * i) + j] += data[(cols * i) + k] * operand2.data[(output.cols * k) + j];
                //std::cout << "op1[" <<(cols * i + k) << "](" << data[cols * i + k] << ")";
                //std::cout << " * ";
                //std::cout << "op2[" << (output.cols * k + j) << "](" << operand2.data[output.cols * k + j] << ") + ";
            }
            //std::cout << " = " << output.data[output.cols * i + j] << std::endl;
        }
    }
    return output;

}

template <typename T>
Mat<T>& Mat<T>::operator=(const Mat<T>& other) {
    if ((void*)this == (void*)(&other))
        return *this;

    for (int i = 0; i < other.rows * other.cols; i++) {
        this->data[i] = (T)(other.data[i]);
    }

    return *this;
}

template <typename T>
template <typename U>
Mat<T>& Mat<T>::operator=(const Mat<U> &&other) {
    if ((void*)this == (void*)(&other))
        return *this;
    
    this->rows = other.rows;
    this->cols = other.cols;
    this->data.reset(new T[other.rows * other.cols]{ 0 });
    for (int i = 0; i < other.rows * other.cols; i++) {
        this->data[i] = (T)(other.data[i]);
    }
    
    return *this;
}