#include "heatequationsolver.h"

#include <BorderRules.h>
#include <gausssolver.h>
#include <BandMatrix.h>
#include <HeatMatrix.h>
#include <parser.h>

template<class T>
QVector<QVector<T>> stdToQtMatrix(const std::vector<std::vector<T>>& m)
{
    QVector<QVector<T>> res(m.size());
    for (int i = 0; i < m.size(); ++i) {
        res[i] = QVector<T>::fromStdVector(m[i]);
    }

    return res;
}

HeatEquationSolver::HeatEquationSolver(const InputData& data) {
    const Point origin = newPoint(data.x0, data.y0);
    auto k_v = getGlobalMatrixAndVector(data.hx, data.hy,
        origin, data.k_x, data.k_y, data.f);

    m_boundaryConditions_1 = QMap<int, float>(data.cond1);
    countBorderRules(k_v.first, k_v.second, data.cond1);
    QVector<QVector<float>> K = stdToQtMatrix(k_v.first);
    QVector<float> V = QVector<float>::fromStdVector(k_v.second);

    m_origin = QVector2D(origin[0], origin[1]);

    m_xoffsets = QVector<CoordDiff>::fromStdVector(data.hx);
    m_yoffsets = QVector<CoordDiff>::fromStdVector(data.hy);

    const bool success = solveSystem(K, V, m_temperatures);
}

QVector<float> HeatEquationSolver::temperatures() const
{
    return m_temperatures;
}

QVector<CoordDiff> HeatEquationSolver::xoffsets() const
{
    return m_xoffsets;
}

QVector<CoordDiff> HeatEquationSolver::yoffsets() const
{
    return m_yoffsets;
}

QVector2D HeatEquationSolver::origin() const
{
    return m_origin;
}

QVector<float> HeatEquationSolver::initialConditions() const
{
    return m_initialConditions;
}

QMap<int, float> HeatEquationSolver::boundaryConditions_1() const
{
    return m_boundaryConditions_1;
}

QMap<QPair<int, int>, HeatEquationSolver::ConvectionData> HeatEquationSolver::boundaryConditions_3() const
{
    return m_boundaryConditions_3;
}