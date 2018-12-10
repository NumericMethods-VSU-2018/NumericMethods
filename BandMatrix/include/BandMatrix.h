#pragma once

#include <vector>

using Matrix = std::vector<std::vector<int>>;

Matrix create2DMatrix(const int size);
Matrix buildBandMatrix(const Matrix& m);