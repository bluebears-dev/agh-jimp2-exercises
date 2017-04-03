//
// Created by pgorski42 on 02.04.17.
//

#ifndef JIMP_EXERCISES_MATRIX_H
#define JIMP_EXERCISES_MATRIX_H

#include <initializer_list>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <utility>
#include <regex>

namespace algebra {
    class Matrix {
        std::complex<double> **array;
        size_t height, width;
        void fill(const std::complex<double> &value);
        void MakeUnitary();
    public:
        Matrix();
        ~Matrix();

        Matrix(size_t height, size_t width);
        Matrix(const std::initializer_list<std::vector<std::complex<double>>> &elements);
        Matrix(const std::string &str_matrix);

        Matrix(const Matrix &matrix);
        Matrix &operator=(const Matrix &matrix);

        Matrix(Matrix &&matrix);
        Matrix &operator=(Matrix &&matrix);

        std::pair<size_t, size_t> Size() const;
        std::string Print() const;
        Matrix Add(const Matrix &matrix) const;
        Matrix Sub(const Matrix &matrix) const;
        Matrix Mul(const Matrix &matrix) const;
        Matrix Mul(const std::complex<double> number) const;
        Matrix Div(const std::complex<double> number) const;
        Matrix Pow(int exponent) const;
    };
}

#endif //JIMP_EXERCISES_MATRIX_H
