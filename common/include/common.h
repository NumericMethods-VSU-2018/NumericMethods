#pragma once

#include <vector>
#include <functional>
#include <map>

using Coord = float;
using CoordDiff = float;
using MathFunc = std::function<float (Coord, Coord)>;

using BoundaryCond1 = std::map<int, float>;

using Vector = std::vector<float>;
using Matrix = std::vector<Vector>;

Matrix create2DMatrix(size_t width, size_t height);