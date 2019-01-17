#pragma once

#include <vector>
#include <functional>
#include <map>

using Coord = double;
using CoordDiff = double;
using MathFunc = std::function<double (Coord, Coord)>;

using BoundaryCond1 = std::map<int, double>;

using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;

Matrix create2DMatrix(size_t width, size_t height);