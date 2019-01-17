#pragma once

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

    HeatEquationSolver(const InputData& data);

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

    bool valid() const;

private:
    bool m_valid;
    QVector<double> m_temperatures;
    QVector<CoordDiff> m_xoffsets;
    QVector<CoordDiff> m_yoffsets;
    QVector<double> m_initialConditions;
    QMap<int, double> m_boundaryConditions_1;
    QMap<QPair<int, int>, ConvectionData> m_boundaryConditions_3;

    QVector2D m_origin;
};
