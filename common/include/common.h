#pragma once

#include <vector>
#include <functional>

using Coord = float;
using CoordDiff = float;
using MathFunc = std::function<float (Coord, Coord)>;

using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;

Matrix create2DMatrix(size_t width, size_t height);