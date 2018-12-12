#include "heatequationsolver.h"

#include <QFile>
#include <QTextStream>
#include <QIODevice>


HeatEquationSolver::HeatEquationSolver(const QString &fileName) {
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    Q_ASSERT(file.isOpen());

    QTextStream in(&file);

    int xoffsetSize = in.readLine().toInt();
    Q_ASSERT(!in.atEnd());
    int yoffsetSize = in.readLine().toInt();
    Q_ASSERT(!in.atEnd());

    QStringList strOrigin = in.readLine().split(' ');
    Q_ASSERT(strOrigin.size() == 2);
    m_origin = QVector2D(strOrigin[0].toFloat(), strOrigin[1].toFloat());

    m_xoffsets.resize(xoffsetSize);
    m_yoffsets.resize(yoffsetSize);

    for (int xoffsetInd = 0; xoffsetInd < xoffsetSize; xoffsetInd++) {
        m_xoffsets[xoffsetInd] = in.readLine().toFloat();
    }
    for (int yoffsetInd = 0; yoffsetInd < yoffsetSize; yoffsetInd++) {
        m_yoffsets[yoffsetInd] = in.readLine().toFloat();
    }

    file.close();

    QVector<float> defaultValues(xoffsetSize);
    defaultValues.fill(0);
    m_temperatures.fill(defaultValues, yoffsetSize);
}

HeatEquationSolver::HeatEquationSolver(const QVector<float> &xoffsets, const QVector<float> &yoffsets, const QPointF &origin)
    : m_xoffsets(xoffsets), m_yoffsets(yoffsets), m_origin(origin) {

    QVector<float> defaultValues(xoffsets.size());
    defaultValues.fill(0);
    m_temperatures.fill(defaultValues, yoffsets.size());
}
