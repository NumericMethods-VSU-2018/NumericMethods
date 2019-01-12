#include "../include/Point.h"
#include <cassert>

Point newPoint(double x, double y) {
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

Point newPoint(const Point &p){
    return newPoint(p[0], p[1]);
}

std::vector<Point> getPoints(std::vector<double> h_x,
                             std::vector<double> h_y,
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

void movePoint(Point &p, double offsetX, double offsetY) {
    p[0] += offsetX;
    p[1] += offsetY;
}

void setPoint(Point &p, double x, double y) {
    p[0] = x;
    p[1] = y;
}

