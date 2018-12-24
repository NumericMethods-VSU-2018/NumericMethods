#pragma once

#include <vector>

using Point = std::vector<double>;

Point operator+(const Point &p1, const Point &p2);
Point operator/(const Point &lhs, const double &rhs);
Point newPoint(double x, double y);
Point newPoint(const Point &p);
void movePoint(Point &p, double offsetX, double offsetY);
void setPoint(Point &p, double x, double y);
std::vector<Point> getPoints(std::vector<double> h_x,
                             std::vector<double> h_y,
                             const Point &origin);

