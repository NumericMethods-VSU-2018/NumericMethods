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
    HeatEquationSolverGLData(const QVector<double> &xoffsets,
                                const QVector<double> &yoffsets,
                                const QVector2D &origin,
                                const QVector<double> temperatures, MeshPattern pattern);
    ~HeatEquationSolverGLData();

    BoundingBox boundingBox() const;
    inline double maxTemperature() const {
        return m_maxTemperature;
    }
    inline double minTemperature() const {
        return m_minTemperature;
    }
    void updatePositions(const QVector<double> &xoffsets,
                           const QVector<double> &yoffsets,
                           const QVector2D &origin);
    void updateColors(QVector<double> temperatures);

    void drawMesh(QOpenGLFunctions_3_3_Compatibility *functions, const QMatrix4x4 &proj, const QMatrix4x4 &view);
    void drawWireframe(QOpenGLFunctions_3_3_Compatibility *functions, const QMatrix4x4 &proj, const QMatrix4x4 &view);
    void drawScale(QOpenGLFunctions_3_3_Compatibility *functions);
    QVector<QVector2D> positions() const;

    int rowCount() const;

    int colCount() const;

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
    double m_maxTemperature;
    double m_minTemperature;
    double minmaxTemperatureColors[6];

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
