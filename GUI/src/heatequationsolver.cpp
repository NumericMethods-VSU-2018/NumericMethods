#include "heatequationsolver.h"

#include <BorderRules.h>
#include <gausssolver.h>
#include <parser.h>
#include <BandMatrix.h>
#include <HeatMatrix.h>

template<class T>
QVector<QVector<T>> stdToQtMatrix(const std::vector<std::vector<T>>& m)
{
    QVector<QVector<T>> res(m.size());
    for (int i = 0; i < m.size(); ++i) {
        res[i] = QVector<T>::fromStdVector(m[i]);
    }

    return res;
}

HeatEquationSolver::HeatEquationSolver(const QString &fileName) {
    const InputData data = parseFile(fileName.toStdString());
    const Point origin = newPoint(data.x0, data.y0);
    auto k_v = getGlobalMatrixAndVector(data.hx, data.hy,
        origin, data.k_x, data.k_y, data.f);

    //m_boundaryConditions_1 = QMap<int, float>(data.cond1);
    //countBorderRules(k_v.first, k_v.second, data.cond1);
    QVector<QVector<float>> K = stdToQtMatrix(k_v.first);
    QVector<float> V = QVector<float>::fromStdVector(k_v.second);

    m_origin = QVector2D(origin[0], origin[1]);

    m_xoffsets = QVector<CoordDiff>::fromStdVector(data.hx);
    m_yoffsets = QVector<CoordDiff>::fromStdVector(data.hy);

    const bool success = solveSystem(K, V, m_temperatures);
}

HeatEquationSolver::HeatEquationSolver(const QVector<float> &xoffsets, const QVector<float> &yoffsets, const QPointF &origin)
    : m_xoffsets(xoffsets), m_yoffsets(yoffsets), m_origin(origin) {

    QVector<float> defaultValues(xoffsets.size());
    defaultValues.fill(0);
    m_temperatures.fill(0, xoffsets.size() * yoffsets.size());
}
