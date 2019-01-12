#include "Point.h"
#include <cassert>

Point newPoint(Coord x, Coord y) {
    Point point(2);
    point[0] = x;
    point[1] = y;
    return point;
}


Point operator/(const Point &lhs, const double &rhs) {
    if (rhs != 0) {
        return newPoint(lhs[0] / rhs, lhs[1] / rhs);
    }
    assert(false);
    return {};
}

Point operator+(const Point &lhs, const Point &&rhs) {
    if (lhs.size() == rhs.size()){
        Point result(rhs.size());
        for (int i = 0; i < rhs.size(); i++) {
            result[i] = lhs[i] + rhs[i];
        }
        return result;
    }
    assert(false);
    return {};
}

Point newPoint(const Point &p){
    return newPoint(p[0], p[1]);
}

std::vector<Point> getPoints(std::vector<CoordDiff> h_x,
                             std::vector<CoordDiff> h_y,
                             const Point &origin) {
    Point current = newPoint(origin);
    const size_t x_size = h_x.size() + 1;
    const size_t y_size = h_y.size() + 1;
    int points_count = x_size * y_size;
    std::vector<Point> points(points_count);
    points[0] = newPoint(current);
    for (int y = 0; y < y_size; y++) {
        points[y * x_size] = newPoint(current);
        for (int x = 0; x < h_x.size(); x++) {
            movePoint(current, h_x[x], 0);
            points[y * x_size + x + 1] = newPoint(current);
        }
        if (y != y_size)
            setPoint(current, origin[0], current[1] + h_y[y]);
    }
//    setPoint(current,0,0);
    return points;
}

void movePoint(Point &p, CoordDiff offsetX, CoordDiff offsetY) {
    p[0] += offsetX;
    p[1] += offsetY;
}

void setPoint(Point &p, Coord x, Coord y) {
    p[0] = x;
    p[1] = y;
}

