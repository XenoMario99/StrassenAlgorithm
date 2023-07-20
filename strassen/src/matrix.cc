#include "matrix.h"

#include <stdexcept>

Matrix::Matrix(int size) : size(size) {
    matrix = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
}

Matrix::Matrix(int size, const std::vector<std::vector<int>>& twoDArr) : size(size), matrix(twoDArr) {}

Matrix operator+(const Matrix& m1, const Matrix& m2) {
    if (m1.size == m2.size) {
        const int size = m1.size;
        Matrix result(size);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result[i][j] = m1[i][j] + m2[i][j];
            }
        }

        return result;

    } else {
        throw std::invalid_argument("The matrices with different dimensions cannot be added or subtracted");
    }
}

Matrix operator-(const Matrix& m1, const Matrix& m2) {
    if (m1.size == m2.size) {
        int size = m1.size;
        Matrix m3(size);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                m3[i][j] = m1[i][j] - m2[i][j];
            }
        }

        return m3;
    } else {
        throw std::invalid_argument("The matrices with different dimensions cannot be added or subtracted");
    }
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    if (m1.size == m2.size) {
        int size = m1.size;
        Matrix m3(size);

        int sum = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                sum = 0;
                for (int k = 0; k < size; k++) {
                    sum += m1[i][k] * m2[k][j];
                }
                m3[i][j] = sum;
            }
        }

        return m3;
    } else {
        throw std::invalid_argument("The scope of this exercise does not cover different size matrices multiplication");
    }
}

std::vector<int> Matrix::operator[](int i) const {
    return matrix.at(i);
}

std::vector<int>& Matrix::operator[](int i) {
    return matrix.at(i);
}

void Matrix::print() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}