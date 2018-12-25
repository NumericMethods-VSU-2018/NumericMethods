#include "heatequationsolver.h"

#include <QFile>
#include <QTextStream>
#include <QIODevice>


HeatEquationSolver::HeatEquationSolver(const QString &fileName) {
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    Q_ASSERT(file.isOpen());

    QTextStream in(&file);

    const int xoffsetSize = in.readLine().toInt();
    Q_ASSERT(!in.atEnd());
    const int yoffsetSize = in.readLine().toInt();
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

    const int vertexCount = xoffsetSize * yoffsetSize;
    m_coefX.resize(vertexCount);
    m_coefY.resize(vertexCount);
    //m_initialConditions.resize(vertexCount);
    m_temperatures.resize(vertexCount);

    for (int i = 0; i < vertexCount; i++) {
        const QString &line = in.readLine();
        const QStringList &splittedLine = line.split(' ');
        m_coefX[i] = splittedLine[0].toFloat();
        m_coefY[i] = splittedLine[1].toFloat();
        //m_initialConditions[i] = splittedLine[2].toFloat();
    }

    const int boundaryConditions_1_size = in.readLine().toInt();
    for (int i = 0; i < boundaryConditions_1_size; i++){
        const QString &line = in.readLine();
        const QStringList &splittedLine = line.split(' ');
        const int boundaryVertInd = splittedLine[0].toInt();
        m_boundaryConditions_1[boundaryVertInd] = splittedLine[1].toFloat();
    }

    const int boundaryConditions_3_size = in.readLine().toInt();
    for (int i = 0; i < boundaryConditions_3_size; i++){
        const QString &line = in.readLine();
        const QStringList &splittedLine = line.split(' ');
        const QPair<int, int> boundaryInd = { splittedLine[0].toInt(), splittedLine[1].toInt() };
        m_boundaryConditions_3[boundaryInd] = { splittedLine[2].toFloat(), splittedLine[3].toFloat() };
    }

    file.close();
    m_temperatures.fill(0, vertexCount);
}

HeatEquationSolver::HeatEquationSolver(const QVector<float> &xoffsets, const QVector<float> &yoffsets, const QPointF &origin)
    : m_xoffsets(xoffsets), m_yoffsets(yoffsets), m_origin(origin) {

    QVector<float> defaultValues(xoffsets.size());
    defaultValues.fill(0);
    m_temperatures.fill(0, xoffsets.size() * yoffsets.size());
}
