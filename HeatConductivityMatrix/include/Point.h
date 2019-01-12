#pragma once

#include <common.h>
#include <vector>

using Point = std::vector<Coord>;

Point operator/(const Point &lhs, const double &rhs);
Point operator+(const Point &lhs, const Point &rhs);
Point newPoint(Coord x, Coord y);
Point newPoint(const Point &p);
void movePoint(Point &p, CoordDiff offsetX, CoordDiff offsetY);
void setPoint(Point &p, Coord x, Coord y);
std::vector<Point> getPoints(std::vector<CoordDiff> h_x,
                             std::vector<CoordDiff> h_y,
                             const Point &origin);

