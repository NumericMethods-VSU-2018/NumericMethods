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

    QVector<float> temperatures() const;
    QVector<CoordDiff> xoffsets() const;
    QVector<CoordDiff> yoffsets() const;
    QVector2D origin() const;
    QVector<float> initialConditions() const;
    QMap<int, float> boundaryConditions_1() const;
    QMap<QPair<int, int>, ConvectionData> boundaryConditions_3() const;

    struct ConvectionData {
        float m_emissionCoef;
        float m_ambientTemperature;
    };

    bool valid() const;

private:
    bool m_valid;
    QVector<float> m_temperatures;
    QVector<CoordDiff> m_xoffsets;
    QVector<CoordDiff> m_yoffsets;
    QVector<float> m_initialConditions;
    QMap<int, float> m_boundaryConditions_1;
    QMap<QPair<int, int>, ConvectionData> m_boundaryConditions_3;

    QVector2D m_origin;
};
