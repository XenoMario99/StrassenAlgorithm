#include "strassen.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <random>

#include "matrix.h"

class StrassenTest : public ::testing::Test {
   public:
    Matrix* matrix;
    Matrix* m2;
    const int size = 16;

   protected:
    void SetUp() override {
        std::random_device rnd;
        std::mt19937 engine{rnd()};
        std::uniform_int_distribution<int> distr{0, 9};

        auto gen = [&]() {
            return distr(engine);
        };

        std::vector<std::vector<int>> vec{std::vector<std::vector<int>>(size, std::vector<int>(size, 0))};

        for (int i = 0; i < size; i++) {
            std::generate(vec[i].begin(), vec[i].end(), gen);
        }

        matrix = new Matrix(size, vec);

        for (int i = 0; i < size; i++) {
            std::generate(vec[i].begin(), vec[i].end(), gen);
        }

        m2 = new Matrix(size, vec);
    }

    void TearDown() override {
        delete matrix;
        delete m2;
    }
};

TEST_F(StrassenTest, divideMatrix_ok) {
    const int numOfDivided = 4;
    std::vector<Matrix> mVec(numOfDivided, Matrix());

    mVec = strassen::divideMatrix(*matrix);

    // First Matrix
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            EXPECT_EQ(mVec[0][i][j], (*matrix)[i][j]);
        }
    }
    // Second Matrix
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            EXPECT_EQ(mVec[1][i][j], (*matrix)[i][j + 8]);
        }
    }
    // Third Matrix
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            EXPECT_EQ(mVec[2][i][j], (*matrix)[i + 8][j]);
        }
    }
    // Fourth Matrix
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            EXPECT_EQ(mVec[3][i][j], (*matrix)[i + 8][j + 8]);
        }
    }
}

TEST_F(StrassenTest, divideAndMergeMatrix_ok) {
    const int numOfDivided = 4;
    std::vector<Matrix> mVec(numOfDivided, Matrix());

    mVec = strassen::divideMatrix(*matrix);
    Matrix newOne = strassen::mergeMatrices(mVec);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            EXPECT_EQ((*matrix)[i][j], newOne[i][j]);
        }
    }
}

TEST_F(StrassenTest, strassenAlgorith_ok) {
    Matrix strassenRes{std::move(strassen::strassen(*matrix, *m2))};
    Matrix ref(size);

    int sum = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sum = 0;
            for (int k = 0; k < size; k++) {
                sum += (*matrix)[i][k] * (*m2)[k][j];
            }
            ref[i][j] = sum;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            EXPECT_EQ(strassenRes[i][j], ref[i][j]);
        }
    }
}