#ifndef HEATEQUATIONSOLVER_H
#define HEATEQUATIONSOLVER_H

#include <common.h>

#include <QString>
#include <QVector>
#include <QVector2D>
#include <QMap>

class InputData;

class HeatEquationSolver
{
public:
    struct ConvectionData;

    HeatEquationSolver(const InputData &data);

    QVector<double> temperatures() const;
    QVector<CoordDiff> xoffsets() const;
    QVector<CoordDiff> yoffsets() const;
    QVector2D origin() const;
    QVector<double> initialConditions() const;
    QMap<int, double> boundaryConditions_1() const;
    QMap<QPair<int, int>, ConvectionData> boundaryConditions_3() const;

    struct ConvectionData {
        double m_emissionCoef;
        double m_ambientTemperature;
    };

private:
    QVector<double> m_temperatures;
    QVector<CoordDiff> m_xoffsets;
    QVector<CoordDiff> m_yoffsets;
    QVector<double> m_initialConditions;
    QMap<int, double> m_boundaryConditions_1;
    QMap<QPair<int, int>, ConvectionData> m_boundaryConditions_3;

    QVector2D m_origin;
};

inline QVector<double> HeatEquationSolver::temperatures() const {
    return m_temperatures;
}

inline QVector<CoordDiff> HeatEquationSolver::xoffsets() const {
    return m_xoffsets;
}
inline QVector<CoordDiff> HeatEquationSolver::yoffsets() const {
    return m_yoffsets;
}

inline QVector2D HeatEquationSolver::origin() const {
    return m_origin;
}

inline QVector<double> HeatEquationSolver::initialConditions() const
{
    return m_initialConditions;
}

inline QMap<int, double> HeatEquationSolver::boundaryConditions_1() const
{
    return m_boundaryConditions_1;
}

inline QMap<QPair<int, int>, HeatEquationSolver::ConvectionData> HeatEquationSolver::boundaryConditions_3() const
{
    return m_boundaryConditions_3;
}


#endif // HEATEQUATIONSOLVER_H
