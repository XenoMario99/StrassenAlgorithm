#pragma once

#include <cmath>
#include <vector>

#include "matrix.h"

namespace strassen {

const int threshold = 2;

std::vector<Matrix> divideMatrix(const Matrix& matrix);
Matrix mergeMatrices(const std::vector<Matrix>& vec);
Matrix strassen(const Matrix&, const Matrix&);

}  // namespace strassen