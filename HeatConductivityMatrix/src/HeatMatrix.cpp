#include "../include/HeatMatrix.h"
#include <cassert>

Matrix init(int width, int height) {
    Matrix matrix(height);
    for (auto &l: matrix) {
        l.resize(width);
    }
    return matrix;
}

Matrix getLocal(const Point &i,
                const Point &j,
                const Point &k,
                const std::function<double(double, double)> &k_x,
                const std::function<double(double, double)> &k_y) {
    // i - 0, j - 1, k - 2
    Matrix local = init(3, 3);
    double space = 0.5 * (j[0] * k[1] - k[0] * j[1] + i[0] * j[1] - i[0] * k[1] + k[0] * i[1] - j[0] * i[1]);
    std::vector<Point> midPoints = {(i + j) / 2, (j + k) / 2, (k + i) / 2};
    std::vector<double> b = {j[1] - k[1], k[1] - i[1], i[1] - j[1]};
    std::vector<double> c = {k[0] - j[0], i[0] - k[0], j[0] - i[0]};

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            for (auto &p: midPoints) {
                local[row][col] +=
                        b[row] * b[col] * k_x(p[0], p[1]) +
                        c[row] * c[col] * k_y(p[0], p[1]);

            }
            local[row][col] *= space / 3;
        }
    }
    return local;
}

Matrix
localToGlobal(const Matrix &local, const int &i, const int &j, const int &k, const int &width, const int &height) {
    Matrix global = init(width, height);
    global[i][i] = local[0][0];
    global[i][j] = local[0][1];
    global[i][k] = local[0][2];
    global[j][i] = local[1][0];
    global[j][j] = local[1][1];
    global[j][k] = local[1][2];
    global[k][i] = local[2][0];
    global[k][j] = local[2][1];
    global[k][k] = local[2][2];
    return global;
}


Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
    if (lhs.size() == rhs.size() && lhs[0].size() == rhs[0].size()) {
        Matrix result = init(lhs[0].size(), lhs.size());
        for (int i = 0; i < lhs.size(); i++) {
            for (int j = 0; j < lhs[0].size(); j++) {
                result[i][j] = lhs[i][j] + rhs[i][j];
            }
        }
        return result;
    }
    assert(false);
    return {};
}

Vector operator+(const Vector &lhs, const Vector &rhs){
    if (lhs.size() == rhs.size()){
        Vector result(rhs.size());
        for (int i = 0; i < rhs.size(); i++) {
            result[i] = lhs[i] + rhs[i];
        }
        return result;
    }
    assert(false);
    return {};
}

Vector getLocalVector(const Point &i,
                      const Point &j,
                      const Point &k,
                      const std::function<double(double, double)> &f) {
    Vector local(3);
    std::vector<Point> midPoints = {(i + j) / 2, (j + k) / 2, (k + i) / 2};
    std::vector<double> b = {j[1] - k[1], k[1] - i[1], i[1] - j[1]};
    std::vector<double> c = {k[0] - j[0], i[0] - k[0], j[0] - i[0]};
    std::vector<double> a = {j[0] * k[1] - k[0] * j[1],
                             k[0] * i[2] - k[1] * i[0],
                             i[0] * j[1] - j[0] * i[1]};
    for (int row = 0; row < 3; row++) {
        for (auto &p: midPoints) {
            local[row] += (a[row] + b[row]*p[0] + c[row]*p[1]) * f(p[0], p[1]);
        }
        local[row] *= 1.5;
    }
    return local;
}

Vector localVectorToGlobal(const Vector &local, const int &i, const int &j, const int &k, const int &size){
    Vector global(size);
    global[i] = local[0];
    global[j] = local[1];
    global[k] = local[2];
    return global;
}

std::pair<Matrix, Vector> getGlobalMatrixAndVector(std::vector<double> h_x,
                                                   std::vector<double> h_y,
                                                   Point origin,
                                                   const std::function<double(double, double)> &k_x,
                                                   const std::function<double(double, double)> &k_y,
                                                   const std::function<double(double, double)> &f) {
    std::vector<Point> points = getPoints(h_x, h_y, origin);
    int width = h_x.size() + 1;
    int height = h_y.size() + 1;
    Matrix global = init(width * height, width * height);
    Vector globalVector(width * height);
    for (int index = 0; index < points.size() - width; index++) {
        if ((index + 1) % width != 0) {
            int i = index;
            int j = index + 1;
            int k = index + width;
            Point p1 = points[i];
            Point p2 = points[j];
            Point p3 = points[k];
            Matrix local = getLocal(p1, p2, p3, k_x, k_y);
            Vector localVector = getLocalVector(p1, p2, p3, f);
            Matrix globalLocal = localToGlobal(local, i, j, k, width * height, width * height);
            Vector globalLocalVector = localVectorToGlobal(localVector, i, j, k, width * height);
            global = global + globalLocal;
            globalVector = globalVector + globalLocalVector;
        }
        if ((index + 1) % height != 0) {
            int i = index + 1;
            int j = index + width;
            int k = index + width + 1;
            Point p1 = points[i];
            Point p2 = points[j];
            Point p3 = points[k];
            Matrix local = getLocal(p1, p2, p3, k_x, k_y);
            Vector localVector = getLocalVector(p1, p2, p3, f);
            Matrix globalLocal = localToGlobal(local, i, j, k, width * height, width * height);
            Vector globalLocalVector = localVectorToGlobal(localVector, i, j, k, width * height);
            global = global + globalLocal;
            globalVector = globalVector + globalLocalVector;
        }

    }
    return std::pair<Matrix, Vector>(global, globalVector);
}
