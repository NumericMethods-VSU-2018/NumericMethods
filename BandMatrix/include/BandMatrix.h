#pragma once

#include <vector>

using Matrix = std::vector<std::vector<int>>;

Matrix create2DMatrix(size_t width, size_t height);
size_t getBandWidth(const Matrix& m);
Matrix buildBandMatrix(const Matrix& m);