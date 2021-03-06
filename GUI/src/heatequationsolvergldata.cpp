#include "heatequationsolvergldata.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QTimer>

#include <QDateTime>
#include <QRandomGenerator>

#include <algorithm>

HeatEquationSolverGLData::HeatEquationSolverGLData(
        const QVector<double> &xoffsets,
        const QVector<double> &yoffsets,
        const QVector2D &origin,
        const QVector<double> temperatures,
        MeshPattern pattern)
    : m_rowCount(yoffsets.size() + 1)
    , m_colCount(xoffsets.size() + 1)
    , m_pattern(pattern)
    , m_positionsVBO(nullptr)
    , m_colorsVBO(nullptr)
    , m_ebo(nullptr)
    , m_maxTemperature(0)
    , m_minTemperature(0)
{
    Q_ASSERT(m_rowCount * m_colCount == temperatures.size());
    buildShaders();

    updatePositions(xoffsets, yoffsets, origin);
    updateColors(temperatures);

    m_vao.create();
    m_vao.bind();

    m_positionsVBO = new QOpenGLBuffer();
    allocateBuffer(m_positionsVBO, m_positions);

    auto functions = QOpenGLContext::currentContext()->functions();
    functions->glEnableVertexAttribArray(0);
    functions->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    m_ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    allocateBuffer(m_ebo, m_indices);

    m_colorsVBO = new QOpenGLBuffer();
    allocateBuffer(m_colorsVBO, m_colors);

    m_wireframeColors.fill(QVector3D(), m_colors.size());


    functions->glEnableVertexAttribArray(1);
    functions->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    m_vao.release();

    m_wireframeColorsVBO = new QOpenGLBuffer();
    allocateBuffer(m_wireframeColorsVBO, m_wireframeColors);
}

HeatEquationSolverGLData::~HeatEquationSolverGLData()
{
    delete m_positionsVBO;
    delete m_colorsVBO;
    delete m_wireframeColorsVBO;
    delete m_ebo;
}

void HeatEquationSolverGLData::updatePositions(
	const QVector<double> &xoffsets,
	const QVector<double> &yoffsets,
	const QVector2D &origin)
{
    QVector2D current = origin;
    m_rowCount = yoffsets.size() + 1;
    m_colCount = xoffsets.size() + 1;
    int newVertexCount = m_rowCount * m_colCount;
    if (newVertexCount != m_positions.size())
        m_positions.resize(newVertexCount);

    for (int rowInd = 0; rowInd < m_rowCount; rowInd++) {
        for (int colInd = 0; colInd < m_colCount; colInd++) {
            int curPosInd = rowInd * m_colCount + colInd;
            const QVector2D pos = current;
            m_positions[curPosInd] = pos;

            if (rowInd < m_rowCount - 1) {
                if (m_pattern == MeshPattern::BotLeft_TopRight) {
                    m_indices.push_back(curPosInd);
                    m_indices.push_back((rowInd + 1) * m_colCount + colInd);
                } else {
                    m_indices.push_back((rowInd + 1) * m_colCount + colInd);
                    m_indices.push_back(curPosInd);
                }
            }
            if (colInd != xoffsets.size())
                current.setX(current.x() + xoffsets[colInd]);
        }

        current.setX(origin.x());
        if (rowInd != yoffsets.size())
            current.setY(current.y() + yoffsets[rowInd]);

        m_indices.push_back(m_positions.size());
    }
    m_bbox = BoundingBox(m_positions);
}

void HeatEquationSolverGLData::updateColors(QVector<double> temperatures) {
    m_minTemperature = qRound(temperatures[0] * 100) / 100;
    m_maxTemperature = m_minTemperature;
    int colorCount = temperatures.size();
    if (colorCount != m_colors.size())
        m_colors.resize(colorCount);

    for (int i = 1; i < temperatures.size(); i++) {
        temperatures[i] = qRound(temperatures[i] * 100) / 100;

        if (m_minTemperature > temperatures[i])
            m_minTemperature = temperatures[i];
        if (m_maxTemperature < temperatures[i])
            m_maxTemperature = temperatures[i];
    }

    double tempRange = m_maxTemperature - m_minTemperature;

    minmaxTemperatureColors[0] = 0.0f;
    minmaxTemperatureColors[1] = 0.0f;
    minmaxTemperatureColors[2] = 1.0f;

    if (qFuzzyIsNull(tempRange)) {
        m_colors.fill(QVector3D(0.0f, 0.0f, 1.0f));
        minmaxTemperatureColors[3] = 0.0f;
        minmaxTemperatureColors[4] = 0.0f;
        minmaxTemperatureColors[5] = 1.0f;
        return;
    }

    for (int vertInd = 0; vertInd < temperatures.size(); vertInd++) {
        const double relTemp = (temperatures[vertInd] - m_minTemperature) / tempRange;

        const QVector3D color(relTemp, 0.0f, 1.0f - relTemp);
        m_colors[vertInd] = color;
    }

    minmaxTemperatureColors[3] = 1.0f;
    minmaxTemperatureColors[4] = 0.0f;
    minmaxTemperatureColors[5] = 0.0f;
}

void HeatEquationSolverGLData::drawWireframe(QOpenGLFunctions_3_3_Compatibility *functions, const QMatrix4x4 &proj, const QMatrix4x4 &view)
{
    m_program.bind();
    m_program.setUniformValue("projMatrix", proj);
    m_program.setUniformValue("viewMatrix", view);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    m_vao.bind();
    m_ebo->bind();
    m_wireframeColorsVBO->bind();

    functions->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    functions->glPrimitiveRestartIndex(m_positions.size());
    functions->glPolygonOffset(0.0f, 0.0f);

    glDrawElements(GL_TRIANGLE_STRIP, m_indices.size(), GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    m_wireframeColorsVBO->release();
    m_ebo->release();
    m_vao.release();
    m_program.release();
}

void HeatEquationSolverGLData::drawScale(QOpenGLFunctions_3_3_Compatibility *functions)
{
    const int segmentCount = 3;
    const double delta = (0.9f - 0.6f) / segmentCount;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    functions->glBegin(GL_QUAD_STRIP);
        functions->glColor3f(minmaxTemperatureColors[0], minmaxTemperatureColors[1], minmaxTemperatureColors[2]);
        functions->glVertex2f(-0.9f, -0.75f);
        functions->glVertex2f(-0.9f, -0.85f);

        functions->glColor3f(minmaxTemperatureColors[3], minmaxTemperatureColors[4], minmaxTemperatureColors[5]);
        functions->glVertex2f(-0.6f, -0.75f);
        functions->glVertex2f(-0.6f, -0.85f);
    functions->glEnd();

    // Mesh
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    functions->glBegin(GL_QUAD_STRIP);
    functions->glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= segmentCount; i++) {
        functions->glVertex2f(-0.9f + i * delta, -0.75f);
        functions->glVertex2f(-0.9f + i * delta, -0.85f);
    }
    functions->glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int HeatEquationSolverGLData::rowCount() const
{
    return m_rowCount;
}

int HeatEquationSolverGLData::colCount() const
{
    return m_colCount;
}

void HeatEquationSolverGLData::drawMesh(QOpenGLFunctions_3_3_Compatibility *functions, const QMatrix4x4 &proj, const QMatrix4x4 &view) {
    m_program.bind();
    m_program.setUniformValue("projMatrix", proj);
    m_program.setUniformValue("viewMatrix", view);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    m_vao.bind();
    m_ebo->bind();
    m_colorsVBO->bind();
    functions->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    functions->glPrimitiveRestartIndex(m_positions.size());
    functions->glPolygonOffset(1.0f, 1.0f);

    glDrawElements(GL_TRIANGLE_STRIP, m_indices.size(), GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    m_colorsVBO->release();
    m_ebo->release();
    m_vao.release();
    m_program.release();
}

void HeatEquationSolverGLData::buildShaders()
{
    m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, m_vertexShaderSource);
    m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, m_fragmentShaderSource);
    m_program.bindAttributeLocation("position", 0);
    m_program.bindAttributeLocation("color", 1);
    m_program.link();
}

template<typename T>
void HeatEquationSolverGLData::allocateBuffer(QOpenGLBuffer* buffer, const QVector<T>& data) {
    buffer->create();
    buffer->bind();
    buffer->setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    buffer->allocate(data.constData(), data.size() * sizeof(T));
}

