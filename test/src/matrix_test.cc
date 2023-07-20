#include "matrix.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <random>

class MatrixTest : public ::testing::Test {
   public:
    const int size = 2;

    Matrix* m1;
    Matrix* m2;

    std::vector<std::vector<int>> vec1{std::vector<std::vector<int>>(size, std::vector<int>(size, 0))};
    std::vector<std::vector<int>> vec2{std::vector<std::vector<int>>(size, std::vector<int>(size, 0))};

   protected:
    void SetUp() override {
        std::random_device rnd;
        std::mt19937 engine{rnd()};
        std::uniform_int_distribution<int> distr{1, 9};

        auto gen = [&engine, &distr]() {
            return distr(engine);
        };

        for (int i = 0; i < size; i++) {
            std::generate(vec1[i].begin(), vec1[i].end(), gen);
            std::generate(vec2[i].begin(), vec2[i].end(), gen);
        }

        m1 = new Matrix(size, vec1);
        m2 = new Matrix(size, vec2);
    }

    void TearDown() override {
        delete m1;
        delete m2;
    }
};

TEST_F(MatrixTest, addMatrices) {
    Matrix m3 = (*m1) + (*m2);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            EXPECT_EQ((vec1[i][j] + vec2[i][j]), m3[i][j]);
        }
    }
}

TEST_F(MatrixTest, subtractMatrices) {
    Matrix m3 = (*m1) - (*m2);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            EXPECT_EQ((vec1[i][j] - vec2[i][j]), m3[i][j]);
        }
    }
}

TEST_F(MatrixTest, mupltiplyMatrices) {
    Matrix m3 = (*m1) * (*m2);
    Matrix ref(size);

    int sum = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sum = 0;
            for (int k = 0; k < size; k++) {
                sum += (*m1)[i][k] * (*m2)[k][j];
            }
            ref[i][j] = sum;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            EXPECT_EQ(m3[i][j], ref[i][j]);
        }
    }
}
