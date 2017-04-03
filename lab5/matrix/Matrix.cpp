//
// Created by pgorski42 on 02.04.17.
//


#include "Matrix.h"

using namespace algebra;
using namespace std;

void Matrix::fill(const complex<double> &value) {
    if (height and width) {
        for (auto i = 0; i < height; ++i)
            for (auto j = 0; j < width; ++j)
                array[i][j] = value;
    }
}

void Matrix::MakeUnitary() {
    if (height and width) {
        for (auto i = 0; i < height; ++i)
            for (auto j = 0; j < width; ++j)
                if (i == j)
                    array[i][j] = 1;
                else
                    array[i][j] = 0;
    }
}

Matrix::Matrix() : height(0), width(0), array(nullptr) {}

Matrix::~Matrix() {
    if (height and width) {
        for (auto i = 0; i < height; ++i)
            delete[] array[i];
        delete[] array;
    }
    array = nullptr;
    height = 0;
    width = 0;
}

Matrix::Matrix(size_t height, size_t width) : height(height), width(width), array(nullptr) {
    if (height and width) {
        array = new complex<double>*;
        for (auto i = 0; i < height; ++i)
            array[i] = new complex<double>[width];
    }
    fill(complex<double>(0.0, 0.0));
}

Matrix::Matrix(const string &str_matrix) {

}

Matrix::Matrix(const initializer_list<vector<complex<double>>> &elements) :
        height(elements.size()), width((*elements.begin()).size()) {
    auto size = (*elements.begin()).size();
    for (auto i = elements.begin() + 1; i < elements.end(); ++i)
        if ((*i).size() != size) {
            size = 0;
            i = elements.end();
        }

    if (height and width and size) {
        array = new complex<double>*;
        for (auto i = 0; i < height; ++i) {
            array[i] = new complex<double>[width];
            auto vec = *(elements.begin() + i);
            for (auto j = 0; j < vec.size(); ++j)
                array[i][j] = vec[j];
        }

    }
}

Matrix::Matrix(const Matrix &matrix) {
    height = matrix.height;
    width = matrix.width;

    if (height and width) {
        array = new complex<double>*;
        for (auto i = 0; i < height; ++i) {
            array[i] = new complex<double>[width];
            for (auto j = 0; j < width; ++j)
                array[i][j] = matrix.array[i][j];
        }
    }
}

Matrix &Matrix::operator=(const Matrix &matrix) {
    if (this != &matrix) {
        this->~Matrix();
        height = matrix.height;
        width = matrix.width;

        if (height and width) {
            array = new complex<double> *;
            for (auto i = 0; i < height; ++i) {
                array[i] = new complex<double>[width];
                for (auto j = 0; j < width; ++j)
                    array[i][j] = matrix.array[i][j];
            }
        }
    }
    return *this;
}

Matrix::Matrix(Matrix &&matrix) {
    height = matrix.height;
    width = matrix.width;
    array = matrix.array;

    matrix.array = nullptr;
    matrix.height = 0;
    matrix.width = 0;
}

Matrix &Matrix::operator=(Matrix &&matrix) {
    if (this != &matrix) {
        this->~Matrix();
        height = matrix.height;
        width = matrix.width;
        array = matrix.array;

        matrix.array = nullptr;
        matrix.height = 0;
        matrix.width = 0;
    }
    return *this;
}

std::pair<size_t, size_t> Matrix::Size() const {
    return pair<size_t, size_t>(height, width);
}

string Matrix::Print() const {
    stringstream str_stream;

    str_stream << '[';
    for (auto i = 0; i < height; ++i) {
        for (auto j = 0; j < width; ++j) {
            str_stream << array[i][j].real() << 'i' << array[i][j].imag();
            if (j != width - 1)
                str_stream << ", ";
        }
        if (i != height - 1)
            str_stream << "; ";
    }
    str_stream << ']';
    return str_stream.str();
}

Matrix Matrix::Add(const Matrix &matrix) const {
    Matrix m(height, width);

    if (height != matrix.height or width != matrix.width)
        return Matrix();

    for (auto i = 0; i < height; ++i)
        for (auto j = 0; j < height; ++j)
            m.array[i][j] = Matrix::array[i][j] + matrix.array[i][j];
    return m;
}

Matrix Matrix::Sub(const Matrix &matrix) const {
    Matrix m(height, width);

    if (height != matrix.height or width != matrix.width)
        return Matrix();

    for (auto i = 0; i < height; ++i)
        for (auto j = 0; j < height; ++j)
            m.array[i][j] = Matrix::array[i][j] - matrix.array[i][j];
    return m;
}

Matrix Matrix::Mul(const Matrix &matrix) const {
    Matrix m(height, matrix.width);

    if (height != matrix.width or width != matrix.height)
        return Matrix();

    for (auto i = 0; i < height; ++i)
        for (auto j = 0; j < matrix.width; ++j) {
            m.array[i][j] = 0;
            for (auto k = 0; k < width; ++k)
                m.array[i][j] += Matrix::array[i][k] * matrix.array[k][j];
        }
    return m;
}

Matrix Matrix::Mul(const std::complex<double> number) const {
    Matrix m(*this);

    for (auto i = 0; i < height; ++i)
        for (auto j = 0; j < width; ++j) {
            for (auto k = 0; k < width; ++k)
                m.array[i][j] *= number;
        }
    return m;
}

Matrix Matrix::Div(const std::complex<double> number) const {
    Matrix m(*this);

    for (auto i = 0; i < height; ++i)
        for (auto j = 0; j < width; ++j) {
            for (auto k = 0; k < width; ++k)
                m.array[i][j] /= number;
        }
    return m;
}

Matrix Matrix::Pow(int exponent) const {
    if (!height or !width)
        return Matrix();
    if (height != width)
        return Matrix();

    if (exponent == 1)
        return *this;
    Matrix pow(height, width);
    pow.MakeUnitary();

    for (auto i = 0; i < exponent; ++i)
        pow = pow.Mul(*this);
    return pow;
}
