#pragma once

#include <common.h>
#include <vector>
#include <map>

struct InputData
{
    size_t Nx, Ny; // количество точек разбиения по направлению x,y
    std::vector<CoordDiff> hx, hy; // и массивы шагов по x, y.

    Coord x0, y0; // координата левого нижнего угла прямоугольной области

    MathFunc k_x, k_y, f; // коэффициенты уравнения
    MathFunc phi; // функция, задающая граничное условие.

    BoundaryCond1 cond1;
};

InputData parseInput(const std::string& input);
InputData parseFile(const std::string& file);
