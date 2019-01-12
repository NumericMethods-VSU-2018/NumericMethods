#pragma once

#include <common.h>
#include <vector>
#include <map>

struct InputData
{
    std::vector<CoordDiff> hx, hy; // массивы шагов по x, y.

    Coord x0, y0; // координата левого нижнего угла прямоугольной области

    MathFunc k_x, k_y, f; // коэффициенты уравнения
    MathFunc phi; // функция, задающая граничное условие.

    BoundaryCond1 cond1;
};

InputData parseInput(const std::string& input);
InputData parseFile(const std::string& file);
