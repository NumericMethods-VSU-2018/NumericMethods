#ifndef HEATEQUATIONSOLVER_H
#define HEATEQUATIONSOLVER_H

#include <QString>
#include <QVector>
#include <QVector2D>

class HeatEquationSolver
{
public:
    HeatEquationSolver(const QString &fileName);
    HeatEquationSolver(const QVector<float> &xoffsets, const QVector<float> &yoffsets, const QPointF& origin);

    QVector<QVector<float>> temperatures() const;
    QVector<float> xoffsets() const;
    QVector<float> yoffsets() const;
    QVector2D origin() const;
private:
    QVector<QVector<float>> m_temperatures;
    QVector<float> m_xoffsets;
    QVector<float> m_yoffsets;
    QVector2D m_origin;
};

inline QVector<QVector<float>> HeatEquationSolver::temperatures() const {
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

#endif // HEATEQUATIONSOLVER_H
