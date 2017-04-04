//
// Created by pgorski42 on 02.04.17.
//


#include <iostream>
#include "Matrix.h"

using namespace algebra;
using namespace std;

void Matrix::Create() {
    if (height_ and width_) {
        array_ = new complex<double>*[height_];
        for (auto i = 0; i < height_; ++i)
            array_[i] = new complex<double>[width_];
    }
}

void Matrix::Copy(const Matrix &matrix) {
    if (height_ and width_) {
        array_ = new complex<double>*[height_];
        for (auto i = 0; i < height_; ++i) {
            array_[i] = new complex<double>[width_];
            for (auto j = 0; j < width_; ++j)
                array_[i][j] = matrix.array_[i][j];
        }
    }
}

void Matrix::Fill(const complex<double> &value) {
    if (height_ and width_) {
        for (auto i = 0; i < height_; ++i)
            for (auto j = 0; j < width_; ++j)
                array_[i][j] = value;
    }
}

void Matrix::MakeUnitary() {
    if (height_ and width_ and height_ == width_) {
        for (auto i = 0; i < height_; ++i)
            for (auto j = 0; j < width_; ++j)
                if (i == j)
                    array_[i][j] = 1;
                else
                    array_[i][j] = 0;
    }
}

void Matrix::SanitizeString(std::string &str) {
    regex pattern("[^0-9.,;i]");
    str = regex_replace(str, pattern, "");
}

std::complex<double> Matrix::ToComplex(const std::string &str) {
    size_t pos = str.find('i');
    double r, im;
    string tmp = str.substr(0, pos);
    if (tmp.empty())
        r = 0.0;
    else
        r = stod(tmp);

    tmp = str.substr(pos + 1, str.length());
    if (tmp.empty())
        im = 0.0;
    else
        im = stod(tmp);

    return {r, im};
}

std::vector<std::string> Matrix::Cut(std::string str, const char chr) {
    vector<string> output;
    size_t i;
    size_t pos = 0;
    while ((i = str.find(chr)) != string::npos) {
        output.push_back(str.substr(pos, i - pos));
        str.erase(i, 1);
        pos = i;
    }
    output.push_back(str.substr(pos, str.length() - pos));
    return output;
}

Matrix::Matrix() : height_(0), width_(0), array_(nullptr) {}

Matrix::~Matrix() {
    if (height_ and width_) {
        for (auto i = 0; i < height_; ++i)
            delete[] array_[i];
        delete[] array_;
    }
    array_ = nullptr;
    height_ = 0;
    width_ = 0;
}

Matrix::Matrix(size_t height, size_t width) : height_(height), width_(width), array_(nullptr) {
    Create();
    Fill(complex<double>(0.0, 0.0));
}

Matrix::Matrix(const string &str_matrix) {
    string str(str_matrix);
    SanitizeString(str);
    auto rows = Cut(str, ';');

    height_ = rows.size();
    array_ = new complex<double>*[height_];
    if (height_) {
        vector<size_t> widths;
        for (auto i = 0; i < rows.size(); ++i) {
            auto cols = Cut(rows[i], ',');
            array_[i] = new complex<double>[cols.size()];
            widths.push_back(cols.size());
            for (auto j = 0; j < cols.size(); ++j)
                array_[i][j] = ToComplex(cols[j]);
        }
        size_t prev = widths[0];
        for (auto width : widths) {
            if (prev != width) {
                this->~Matrix();
                return;
            }
            prev = width;
        }
        width_ = widths[0];
    }
}

Matrix::Matrix(const initializer_list<vector<complex<double>>> &elements) :
        height_(elements.size()), width_((*elements.begin()).size()) {
    if (height_ and width_) {
        array_ = new complex<double>*;
        vector<size_t> widths;
        for (auto i = 0; i < height_; ++i) {
            array_[i] = new complex<double>[width_];
            auto vec = *(elements.begin() + i);
            widths.push_back(vec.size());
            for (auto j = 0; j < vec.size(); ++j)
                array_[i][j] = vec[j];
        }
        size_t prev = widths[0];
        for (auto width : widths) {
            if (prev != width) {
                this->~Matrix();
                return;
            }
            prev = width;
        }
        width_ = widths[0];
    }
}

Matrix::Matrix(const Matrix &matrix) {
    height_ = matrix.height_;
    width_ = matrix.width_;

    Copy(matrix);
}

Matrix &Matrix::operator=(const Matrix &matrix) {
    if (this != &matrix) {
        this->~Matrix();
        height_ = matrix.height_;
        width_ = matrix.width_;

        Copy(matrix);
    }
    return *this;
}

Matrix::Matrix(Matrix &&matrix) {
    height_ = matrix.height_;
    width_ = matrix.width_;
    array_ = matrix.array_;

    matrix.array_ = nullptr;
    matrix.height_ = 0;
    matrix.width_ = 0;
}

Matrix &Matrix::operator=(Matrix &&matrix) {
    if (this != &matrix) {
        this->~Matrix();
        height_ = matrix.height_;
        width_ = matrix.width_;
        array_ = matrix.array_;

        matrix.array_ = nullptr;
        matrix.height_ = 0;
        matrix.width_ = 0;
    }
    return *this;
}

std::pair<size_t, size_t> Matrix::Size() const {
    return pair<size_t, size_t>(height_, width_);
}

string Matrix::Print() const {
    stringstream str_stream;

    str_stream << '[';
    for (auto i = 0; i < height_; ++i) {
        for (auto j = 0; j < width_; ++j) {
            str_stream << array_[i][j].real() << 'i' << array_[i][j].imag();
            if (j != width_ - 1)
                str_stream << ", ";
        }
        if (i != height_ - 1)
            str_stream << "; ";
    }
    str_stream << ']';
    return str_stream.str();
}

Matrix Matrix::Add(const Matrix &matrix) const {
    Matrix m(height_, width_);

    if (height_ != matrix.height_ or width_ != matrix.width_)
        return Matrix();

    for (auto i = 0; i < height_; ++i)
        for (auto j = 0; j < height_; ++j)
            m.array_[i][j] = Matrix::array_[i][j] + matrix.array_[i][j];
    return m;
}

Matrix Matrix::Sub(const Matrix &matrix) const {
    Matrix m(height_, width_);

    if (height_ != matrix.height_ or width_ != matrix.width_)
        return Matrix();

    for (auto i = 0; i < height_; ++i)
        for (auto j = 0; j < height_; ++j)
            m.array_[i][j] = Matrix::array_[i][j] - matrix.array_[i][j];
    return m;
}

Matrix Matrix::Mul(const Matrix &matrix) const {
    Matrix m(height_, matrix.width_);

    if (height_ != matrix.width_ or width_ != matrix.height_)
        return Matrix();

    for (auto i = 0; i < height_; ++i)
        for (auto j = 0; j < matrix.width_; ++j) {
            m.array_[i][j] = 0;
            for (auto k = 0; k < width_; ++k)
                m.array_[i][j] += Matrix::array_[i][k] * matrix.array_[k][j];
        }
    return m;
}

Matrix Matrix::Mul(const std::complex<double> number) const {
    Matrix m(*this);

    for (auto i = 0; i < height_; ++i)
        for (auto j = 0; j < width_; ++j) {
            for (auto k = 0; k < width_; ++k)
                m.array_[i][j] *= number;
        }
    return m;
}

Matrix Matrix::Div(const std::complex<double> number) const {
    Matrix m(*this);

    for (auto i = 0; i < height_; ++i)
        for (auto j = 0; j < width_; ++j) {
            for (auto k = 0; k < width_; ++k)
                m.array_[i][j] /= number;
        }
    return m;
}

Matrix Matrix::Pow(int exponent) const {
    if (!height_ or !width_)
        return Matrix();
    if (height_ != width_)
        return Matrix();

    if (exponent == 1)
        return *this;
    Matrix pow(height_, width_);
    pow.MakeUnitary();

    for (auto i = 0; i < exponent; ++i)
        pow = pow.Mul(*this);
    return pow;
}
