#ifndef INC_10TH_HW_MATRIX_H
#define INC_10TH_HW_MATRIX_H

#include <iostream>
#include <array>

template<typename element, size_t height, size_t width>
class Matrix {
private:
    std::array<element, width * height> data_;

    class Request;

public:
    Matrix(const element &value = 0);

    const element &get(size_t row, size_t column) const;

    void set(size_t row, size_t column, const element &value);

    void print(std::ostream &os = std::cout) const;

    Matrix &operator++();

    Matrix operator++(int);

    Request operator[](size_t row);

    const Request operator[](size_t row) const;

};

template<typename element, size_t height, size_t width>
Matrix<element, height, width>::Matrix(const element &value) {
    data_.fill(value);
}

template<typename element, size_t height, size_t width>
const element &Matrix<element, height, width>::get(size_t row, size_t column) const {
    return data_[row * width + column];
}

template<typename element, size_t height, size_t width>
void Matrix<element, height, width>::set(size_t row, size_t column, const element &value) {
    data_[row * width + column] = value;
}

template<typename element, size_t height, size_t width>
std::ostream &operator<<(std::ostream &os, const Matrix<element, height, width> &matrix) {
    matrix.print(os);
    return os;
}

template<typename element, size_t height, size_t width>
void Matrix<element, height, width>::print(std::ostream &os) const {
    os << "[";
    for (size_t r = 0; r < height; ++r) {
        os << "[";
        for (size_t c = 0; c < width; ++c) {
            if (c == width - 1) {
                os << get(r, c);
            } else {
                os << get(r, c) << ", ";
            }
        }
        if (r == height - 1) {
            os << "]";
        } else {
            os << "], ";
        }
    }
    os << "]";
}

template<typename element, size_t height, size_t width>
Matrix<element, height, width> &Matrix<element, height, width>::operator++() {
    for (size_t r = 0; r < height; ++r) {
        for (size_t c = 0; c < width; ++c) {
            ++data_[r * width + c];
        }
    }
    return *this;
}

template<typename element, size_t height, size_t width>
Matrix<element, height, width> Matrix<element, height, width>::operator++(int) {
    Matrix<element, height, width> temp = *this;
    for (size_t r = 0; r < height; ++r) {
        for (size_t c = 0; c < width; ++c) {
            ++data_[r * width + c];
        }
    }
    return temp;
}

template<typename element, size_t height, size_t width>
class Matrix<element, height, width>::Request {

    friend class Matrix<element, height, width>;

private:
    const Matrix<element, height, width> &matrix_;
    size_t row_{};

    Request(const Matrix<element, height, width> &matrix, size_t row);

public:
    element &operator[](size_t column);

    const element &operator[](size_t column) const;
};

template<typename element, size_t height, size_t width>
Matrix<element, height, width>::Request::Request(const Matrix<element, height, width> &matrix, size_t row) : matrix_(
        matrix), row_(row) {}

template<typename element, size_t height, size_t width>
typename Matrix<element, height, width>::Request Matrix<element, height, width>::operator[](size_t row) {
    return Request(*this, row);
}

template<typename element, size_t height, size_t width>
const typename Matrix<element, height, width>::Request Matrix<element, height, width>::operator[](size_t row) const {
    return Request(*this, row);
}

template<typename element, size_t height, size_t width>
element &Matrix<element, height, width>::Request::operator[](size_t column) {
    auto &new_matrix = const_cast<Matrix<element, height, width> &>(matrix_);

    return new_matrix.data_[row_ * width + column];
}

template<typename element, size_t height, size_t width>
const element &Matrix<element, height, width>::Request::operator[](size_t column) const {
    return matrix_.data_[row_ * width + column];
}

template<typename element, size_t height, size_t width>
Matrix<element, height, width> operator+(const Matrix<element, height, width> &matrix, const element &increment) {
    Matrix<element, height, width> temp = matrix;
    for (size_t r = 0; r < height; ++r) {
        for (size_t c = 0; c < width; ++c) {
            temp[r][c] += increment;
        }
    }
    return temp;
}

template<typename element, size_t height, size_t width>
Matrix<element, height, width> operator*(const Matrix<element, height, width> &matrix, const element &factor) {
    Matrix<element, height, width> temp = matrix;
    for (size_t r = 0; r < height; ++r) {
        for (size_t c = 0; c < width; ++c) {
            temp[r][c] *= factor;
        }
    }
    return temp;
}

template<typename element, size_t height, size_t width>
Matrix<element, height, width>
operator+(const Matrix<element, height, width> &matrix1, const Matrix<element, height, width> &matrix2) {
    Matrix<element, height, width> result = matrix1;
    for (size_t r = 0; r < height; ++r) {
        for (size_t c = 0; c < width; ++c) {
            result[r][c] += matrix2[r][c];
        }
    }
    return result;
}

template<typename element, size_t height, size_t width, size_t depth>
Matrix<element, height, width>
operator*(const Matrix<element, height, depth> &matrix1, const Matrix<element, depth, width> &matrix2) {
    Matrix<element, height, width> result;
    for (size_t r = 0; r < height; ++r) {
        for (size_t c = 0; c < width; ++c) {
            result[r][c] = 0;
            for (size_t i = 0; i < depth; ++i) {
                result[r][c] += matrix1[r][i] * matrix2[i][c];
            }
        }
    }
    return result;
}


#endif //INC_10TH_HW_MATRIX_H
