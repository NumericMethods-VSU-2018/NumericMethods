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
    int points_count = (h_x.size() + 1) * (h_y.size() + 1);
    std::vector<Point> points(points_count);
    points[0] = newPoint(current);
    for (int i = 0; i < h_y.size() + 1; i++) {
        for (int j = 0; j < h_x.size(); j++) {
            movePoint(current, h_x[j], 0);
            points[i * (h_x.size() + 1) + j + 1] = newPoint(current);
        }
        setPoint(current, 0, current[1] + h_y[i]);
        if(i != h_y.size()) {
            points[i * (h_x.size() + 1) + h_y.size() + 1] = newPoint(current);
        }
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

