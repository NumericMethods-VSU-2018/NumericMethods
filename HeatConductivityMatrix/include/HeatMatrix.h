#pragma once
#include "Point.h"
#include <vector>
#include <functional>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

Matrix init(int height, int width);
Matrix getLocal(const Point &i,
                const Point &j,
                const Point &k,
                const std::function<double(double, double)> &k_x,
                const std::function<double(double, double)> &k_y);
Matrix localToGlobal(const Matrix &local,
                     const int &i, const int &j,const int &k, const int& width, const int& height);
std::pair<Matrix, Vector> getGlobalMatrixAndVector(std::vector<double> h_x,
                                                   std::vector<double> h_y,
                                                   Point origin,
                                                   const std::function<double(double, double)> &k_x,
                                                   const std::function<double(double, double)> &k_y,
                                                   const std::function<double(double, double)> &f);
Matrix operator+(const Matrix &lhs, const Matrix &rhs);
Vector getLocalVector(const Point &i,
                      const Point &j,
                      const Point &k,
                      const std::function<double(double, double)> &f);
Vector localVectorToGlobal(const Vector &local, const int &i, const int &j, const int &k, const int &size);
Vector operator+(const Vector &lhs, const Vector &rhs);


