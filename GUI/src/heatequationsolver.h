#ifndef HEATEQUATIONSOLVER_H
#define HEATEQUATIONSOLVER_H

#include <QString>
#include <QVector>
#include <QVector2D>
#include <QMap>


class HeatEquationSolver
{
public:
    struct ConvectionData;

    HeatEquationSolver(const QString &fileName);
    HeatEquationSolver(const QVector<float> &xoffsets, const QVector<float> &yoffsets, const QPointF& origin);

    QVector<float> temperatures() const;
    QVector<float> xoffsets() const;
    QVector<float> yoffsets() const;
    QVector2D origin() const;
    QVector<float> coefX() const;
    QVector<float> coefY() const;
    QVector<float> initialConditions() const;
    QMap<int, float> boundaryConditions_1() const;
    QMap<QPair<int, int>, ConvectionData> boundaryConditions_3() const;

    struct ConvectionData {
        float m_emissionCoef;
        float m_ambientTemperature;
    };

private:
    QVector<float> m_temperatures;
    QVector<float> m_xoffsets;
    QVector<float> m_yoffsets;
    QVector<float> m_coefX;
    QVector<float> m_coefY;
    QVector<float> m_initialConditions;
    QMap<int, float> m_boundaryConditions_1;
    QMap<QPair<int, int>, ConvectionData> m_boundaryConditions_3;

    QVector2D m_origin;
};

inline QVector<float> HeatEquationSolver::temperatures() const {
    return m_temperatures;
}

inline QVector<float> HeatEquationSolver::xoffsets() const {
    return m_xoffsets;
}
inline QVector<float> HeatEquationSolver::yoffsets() const {
    return m_yoffsets;
}

inline QVector2D HeatEquationSolver::origin() const {
    return m_origin;
}


inline QVector<float> HeatEquationSolver::coefX() const
{
    return m_coefX;
}

inline QVector<float> HeatEquationSolver::coefY() const
{
    return m_coefY;
}

inline QVector<float> HeatEquationSolver::initialConditions() const
{
    return m_initialConditions;
}

inline QMap<int, float> HeatEquationSolver::boundaryConditions_1() const
{
    return m_boundaryConditions_1;
}

inline QMap<QPair<int, int>, HeatEquationSolver::ConvectionData> HeatEquationSolver::boundaryConditions_3() const
{
    return m_boundaryConditions_3;
}


#endif // HEATEQUATIONSOLVER_H
