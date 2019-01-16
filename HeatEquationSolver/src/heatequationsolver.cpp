#include "heatequationsolver.h"

#include <BorderRules.h>
#include <gausssolver.h>
#include <BandMatrix.h>
#include <HeatMatrix.h>
#include <parser.h>
#include <QDebug>

namespace
{

template<class T>
QVector<QVector<T>> stdToQtMatrix(const std::vector<std::vector<T>>& m)
{
    QVector<QVector<T>> res(m.size());
    for (int i = 0; i < m.size(); ++i) {
        res[i] = QVector<T>::fromStdVector(m[i]);
    }

    return res;
}

std::map<int, float> getBoundCond(
    Coord x0, Coord y0,
    const std::vector<float>& hx,
    const std::vector<float>& hy,
    MathFunc phi)
{
    std::map<int, float> cond1;
    Coord x = x0;
    Coord y = y0;

    const auto rowCount = hy.size() + 1;
    const auto colCount = hx.size() + 1;

    for (int rowInd = 0; rowInd < rowCount; rowInd++) {
        for (int colInd = 0; colInd < colCount; colInd++) {
            if (rowInd == 0 || rowInd == rowCount - 1 || colInd == 0 || colInd == colCount - 1) {
                int curPosInd = rowInd * colCount + colInd;
                cond1[curPosInd] = phi(x, y);
            }

            if (colInd != hx.size())
                x += hx[colInd];
        }

        x = x0;
        if (rowInd != hy.size())
            y += hy[rowInd];

    }

    return cond1;
}

}

HeatEquationSolver::HeatEquationSolver(const InputData& data) {
    const Point origin = newPoint(data.x0, data.y0);
    auto k_v = getGlobalMatrixAndVector(data.hx, data.hy,
        origin, data.k_x, data.k_y, data.f);

    const auto cond1 = getBoundCond(data.x0, data.y0, data.hx, data.hy, data.phi);
    m_boundaryConditions_1 = QMap<int, float>(cond1);
    countBorderRules(k_v.first, k_v.second, cond1);
    QVector<QVector<float>> K = stdToQtMatrix(k_v.first);
    QVector<float> V = QVector<float>::fromStdVector(k_v.second);

    m_origin = QVector2D(origin[0], origin[1]);

    m_xoffsets = QVector<CoordDiff>::fromStdVector(data.hx);
    m_yoffsets = QVector<CoordDiff>::fromStdVector(data.hy);

    m_valid = solveSystem(K, V, m_temperatures);
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

bool HeatEquationSolver::valid() const
{
    return m_valid;
}
