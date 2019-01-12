#pragma once

#include <vector>

using Vector = std::vector<int>;
using Matrix = std::vector<Vector>;

Matrix create2DMatrix(size_t width, size_t height);