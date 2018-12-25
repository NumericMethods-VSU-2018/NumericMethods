#pragma once
#include "Point.h"
#include <vector>

using Matrix = std::vector<std::vector<double>>;

Matrix init(int height, int width);
Matrix getLocal(const Point &i, const Point &j, const Point &k);
Matrix localToGlobal(const Matrix &local,
                     const int &i, const int &j,const int &k, const int& width, const int& height);
Matrix getGlobal(std::vector<double> h_x,
                 std::vector<double> h_y,
                 Point origin);
Matrix operator+(const Matrix &lhs, const Matrix &rhs);



