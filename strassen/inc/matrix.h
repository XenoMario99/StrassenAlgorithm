#pragma once

#include <iostream>
#include <vector>

class Matrix {
   private:
    int size = 0;
    std::vector<std::vector<int>> matrix;

   public:
    Matrix() = default;
    explicit Matrix(int);
    Matrix(int, const std::vector<std::vector<int>>&);
    Matrix(const Matrix&) = default;
    Matrix(Matrix&&) = default;
    Matrix& operator=(const Matrix&) = default;
    Matrix& operator=(Matrix&&) = default;
    ~Matrix() = default;

    friend Matrix operator+(const Matrix& m1, const Matrix& m2);
    friend Matrix operator-(const Matrix& m1, const Matrix& m2);
    friend Matrix operator*(const Matrix& m1, const Matrix& m2);

    std::vector<int> operator[](int i) const;
    std::vector<int>& operator[](int i);

    inline int getSize() const { return size; }

    void print() const;
};