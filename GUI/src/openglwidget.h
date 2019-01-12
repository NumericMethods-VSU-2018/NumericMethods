#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Compatibility>
#include <QOpenGLFramebufferObject>
#include <QPixmap>

#include "heatequationsolver.h"
#include "heatequationsolvergldata.h"
#include "camera.h"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Compatibility
{
public:
    OpenGLWidget(HeatEquationSolver *solver, QWidget *parent = nullptr);

    void fitToScreen();

    ~OpenGLWidget() override;
    bool isDrawOverlay() const;
    void toggleOverlay();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Camera *m_camera;
    HeatEquationSolver *m_solver;
    HeatEquationSolverGLData *m_solverGLData;
    QOpenGLFramebufferObject *m_framebuffer;

    QPixmap m_pixmap;
    bool m_isPan;
    bool m_isDrawOverlay;
    QPoint m_lastMousePos;

    void drawOverlay();
    void drawScaleOverlay(QPainter &painter);
};

#endif // OPENGLWIDGET_H
