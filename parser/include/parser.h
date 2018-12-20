#pragma once

#include <functional>
#include <vector>

using Coord = float;
using CoordDiff = float;
using MathFunc = std::function<float (Coord, Coord)>;

struct InputData
{
    size_t Nx, Ny; // количество точек разбиения по направлению x,y
    std::vector<CoordDiff> hx, hy; // и массивы шагов по x, y.

    Coord x0, y0; // координата левого нижнего угла прямоугольной области

    MathFunc k_x, k_y, f; // коэффициенты уравнения
    MathFunc phi; // функция, задающая граничное условие.
};

InputData parseInput(const std::string& input);
InputData parseFil(const std::string& file);
