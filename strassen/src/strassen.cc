#include "strassen.h"

#include <algorithm>

bool isPowerOfTwo(int num) {
    if (num == 0) return false;

    return (std::ceil(std::log2(num)) == std::floor(std::log2(num)));
}

std::vector<Matrix> strassen::divideMatrix(const Matrix& matrix) {  // const ref
    int size = matrix.getSize();
    if (size >= 4) {
        if (isPowerOfTwo(size)) {
            constexpr int mAmount = 4;
            int steps = size / 2;

            std::vector<Matrix> dividedM{std::vector<Matrix>(mAmount, Matrix(steps))};

            int iTres = 0, jTres = 0;

            for (int mNum = 0; mNum < mAmount; mNum++) {
                for (int i = 0 + iTres; i < steps + iTres; i++) {
                    for (int j = 0 + jTres; j < steps + jTres; j++) {
                        dividedM[mNum][i - iTres][j - jTres] = matrix[i][j];
                    }
                }

                switch (mNum) {
                    case 0: {
                        jTres += steps;
                    } break;
                    case 1: {
                        jTres -= steps;
                        iTres += steps;
                    } break;
                    case 2: {
                        jTres += steps;
                    } break;
                }
            }

            return dividedM;

        } else {
            throw std::invalid_argument("Cannot divide matrix which size is not a power of two");
        }
    } else {
        throw std::invalid_argument("Matrix is to small to divide");
    }
}

Matrix strassen::mergeMatrices(const std::vector<Matrix>& vec) {
    int vecSize = vec.size();

    if (vecSize == 4) {
        if (std::any_of(vec.begin(), vec.end(), [](const Matrix& m) { return !isPowerOfTwo(m.getSize()); })) {
            throw std::invalid_argument("Cannot merge matrix which size is not a power of two");
        }

        if (std::any_of(vec.begin(), vec.end(), [&](const Matrix& m) { return m.getSize() != vec.at(0).getSize(); })) {
            throw std::invalid_argument("Cannot merge different sizes matrices");
        }

        int mSize = vec.at(0).getSize();

        Matrix matrix(2 * mSize);

        int iTres = 0, jTres = 0;

        for (int mNum = 0; mNum < vecSize; mNum++) {
            for (int i = 0 + iTres; i < mSize + iTres; i++) {
                for (int j = 0 + jTres; j < mSize + jTres; j++) {
                    matrix[i][j] = vec[mNum][i - iTres][j - jTres];
                }
            }

            switch (mNum) {
                case 0: {
                    jTres += mSize;
                } break;
                case 1: {
                    jTres -= mSize;
                    iTres += mSize;
                } break;
                case 2: {
                    jTres += mSize;
                } break;
                default:
                    break;
            }
        }
        return matrix;

    } else {
        throw std::invalid_argument("Only four matrices can be merged into one");
    }
}

Matrix strassen::strassen(const Matrix& m1, const Matrix& m2) {  // const ref
    if (m1.getSize() == m2.getSize()) {
        int size = m1.getSize();

        if (size <= threshold) {
            return m1 * m2;
        } else {
            std::vector<Matrix> m1Div{std::move(divideMatrix(m1))};
            std::vector<Matrix> m2Div{std::move(divideMatrix(m2))};

            std::vector<Matrix> mArr{std::vector<Matrix>(7, Matrix(size / 2))};

            mArr[0] = strassen(std::move(m1Div[0] + m1Div[3]), std::move(m2Div[0] + m2Div[3]));
            mArr[1] = strassen(std::move(m1Div[2] + m1Div[3]), std::move(m2Div[0]));
            mArr[2] = strassen(std::move(m1Div[0]), std::move(m2Div[1] - m2Div[3]));
            mArr[3] = strassen(std::move(m1Div[3]), std::move(m2Div[2] - m2Div[0]));
            mArr[4] = strassen(std::move(m1Div[0] + m1Div[1]), std::move(m2Div[3]));
            mArr[5] = strassen(std::move(m1Div[2] - m1Div[0]), std::move(m2Div[0] + m2Div[1]));
            mArr[6] = strassen(std::move(m1Div[1] - m1Div[3]), std::move(m2Div[2] + m2Div[3]));

            std::vector<Matrix> dividedResult{std::vector<Matrix>(4, Matrix(size / 2))};

            dividedResult[0] = std::move(mArr[0] + mArr[3] - mArr[4] + mArr[6]);
            dividedResult[1] = std::move(mArr[2] + mArr[4]);
            dividedResult[2] = std::move(mArr[1] + mArr[3]);
            dividedResult[3] = std::move(mArr[0] + mArr[2] - mArr[1] + mArr[5]);

            Matrix result{std::move(mergeMatrices(dividedResult))};

            return result;
        }

    } else {
        throw std::invalid_argument("The scope of this exercise does not cover different size matrices multiplication");
    }
}