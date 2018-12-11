#ifndef HEATEQUATIONSOLVERGLDATA_H
#define HEATEQUATIONSOLVERGLDATA_H

#include "boundingbox.h"
#include <QVector>
#include <QPointF>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Compatibility>

enum MeshPattern { BotLeft_TopRight, TopLeft_BotRight };

class HeatEquationSolverGLData
{
public:
    HeatEquationSolverGLData(const QVector<float> &xoffsets,
                                const QVector<float> &yoffsets,
                                const QVector2D &origin,
                                const QVector<QVector<float>> temperatures, MeshPattern pattern);
    ~HeatEquationSolverGLData();

    BoundingBox boundingBox() const;
    void updatePositions(const QVector<float> &xoffsets,
                           const QVector<float> &yoffsets,
                           const QVector2D &origin);
    void updateColors(const QVector<QVector<float>> temperatures);

    void drawMesh(QOpenGLFunctions_3_3_Compatibility *functions, const QMatrix4x4 &proj, const QMatrix4x4 &view);
    void drawWireframe(QOpenGLFunctions_3_3_Compatibility *functions, const QMatrix4x4 &proj, const QMatrix4x4 &view);
    QVector<QVector2D> positions() const;

private:
    const QString m_vertexShaderSource = "vert.glsl";
    const QString m_fragmentShaderSource = "frag.glsl";
    MeshPattern m_pattern;
    QVector<QVector2D> m_positions;
    int m_rowCount;
    int m_colCount;
    QVector<QVector3D> m_colors;
    QVector<QVector3D> m_wireframeColors;
    QVector<unsigned> m_indices;

    BoundingBox m_bbox;
    QOpenGLShaderProgram m_program;

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer *m_positionsVBO;
    QOpenGLBuffer *m_colorsVBO;
    QOpenGLBuffer *m_wireframeColorsVBO;
    QOpenGLBuffer *m_ebo;

    template<typename T>
    void allocateBuffer(QOpenGLBuffer* buffer, const QVector<T>& data);
    void buildShaders();
};

inline BoundingBox HeatEquationSolverGLData::boundingBox() const {
    return m_bbox;
}
inline QVector<QVector2D> HeatEquationSolverGLData::positions() const {
    return m_positions;
}

#endif // HEATEQUATIONSOLVERGLDATA_H
