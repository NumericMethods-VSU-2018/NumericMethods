#pragma once
#include "Point.h"

#include <common.h>

#include <vector>
#include <functional>

Matrix init(int height, int width);
Matrix getLocal(const Point &i,
                const Point &j,
                const Point &k,
                const MathFunc &k_x,
                const MathFunc &k_y);
Matrix localToGlobal(const Matrix &local,
                     const int &i, const int &j,const int &k, const int& width, const int& height);
std::pair<Matrix, Vector> getGlobalMatrixAndVector(std::vector<CoordDiff> h_x,
                                                   std::vector<CoordDiff> h_y,
                                                   Point origin,
                                                   const MathFunc &k_x,
                                                   const MathFunc &k_y,
                                                   const MathFunc &f);
Matrix operator+(const Matrix &lhs, const Matrix &rhs);
Vector getLocalVector(const Point &i,
                      const Point &j,
                      const Point &k,
                      const MathFunc &f);
Vector localVectorToGlobal(const Vector &local, const int &i, const int &j, const int &k, const int &size);
Vector operator+(const Vector &lhs, const Vector &rhs);


