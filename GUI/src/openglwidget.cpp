#include "openglwidget.h"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QtMath>
#include <QOpenGLFramebufferObject>

OpenGLWidget::OpenGLWidget(HeatEquationSolver *solver, QWidget *parent)
    : QOpenGLWidget(parent), m_solver(solver), m_isPan(false), m_isDrawOverlay(true)
{
    QSurfaceFormat format;
    format.setSamples(8);
    format.setProfile(QSurfaceFormat::NoProfile);
    setFormat(format);
}

void OpenGLWidget::fitToScreen()
{
    m_camera->fitToScreen(m_solverGLData->boundingBox());
    update();
}

OpenGLWidget::~OpenGLWidget() {
    delete m_camera;
    delete m_solverGLData;
    delete m_framebuffer;
}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(0.3, 0.3, 0.3, 1);
    glEnable(GL_PRIMITIVE_RESTART);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_OFFSET_FILL);

    m_camera = new Camera();
    m_solverGLData = new HeatEquationSolverGLData(m_solver->xoffsets(),
                                                  m_solver->yoffsets(),
                                                  m_solver->origin(),
                                                  m_solver->temperatures(), MeshPattern::BotLeft_TopRight);
    m_framebuffer = new QOpenGLFramebufferObject(size(), QOpenGLFramebufferObject::Attachment::Depth);
}

void OpenGLWidget::paintGL() {
    m_framebuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_solverGLData->drawMesh(this, m_camera->projection(), m_camera->view());

    if (m_isDrawOverlay) {
        m_solverGLData->drawWireframe(this, m_camera->projection(), m_camera->view());
        m_pixmap.convertFromImage(m_framebuffer->toImage());
        drawOverlay();
    } else {
        m_pixmap.convertFromImage(m_framebuffer->toImage());
    }


    m_framebuffer->release();
}

void OpenGLWidget::resizeGL(int width, int height) {
    m_camera->resize(width, height);
    delete m_framebuffer;
    m_framebuffer = new QOpenGLFramebufferObject(size(), QOpenGLFramebufferObject::Attachment::Depth);
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        m_isPan = true;
        m_lastMousePos = event->pos();
        update();
    }
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPan) {
        int dx = event->pos().x() - m_lastMousePos.x();
        int dy = event->pos().y() - m_lastMousePos.y();
        float speed = 0.002f * m_solverGLData->boundingBox().diag().length();
        m_camera->move(dx, dy, speed);

        update();
    }

    m_lastMousePos = event->pos();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        m_isPan = false;
        update();
    }
}

void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    m_camera->zoom(event->angleDelta().y());

    update();
}

void OpenGLWidget::paintEvent(QPaintEvent *event)
{
    QOpenGLWidget::paintEvent(event);
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, width(), height(), m_pixmap);
    painter.end();
}

void OpenGLWidget::drawOverlay()
{
    QPainter painter;
    painter.begin(&m_pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(Qt::black);

    const QVector<float> xoffsets = m_solver->xoffsets();
    const QVector<float> yoffsets = m_solver->yoffsets();
    const QVector2D origin = m_solver->origin();
    int minDist = std::numeric_limits<int>::max();

    for (int rowInd = 0; rowInd < yoffsets.size(); rowInd++) {
        for (int colInd = 0; colInd < xoffsets.size(); colInd++){

            const QVector2D curPos(origin.x() + xoffsets[colInd], origin.y() + yoffsets[rowInd]);
            const QPoint screenCurPos = m_camera->worldToScreen(curPos);

            if (colInd < xoffsets.size() - 1) {
                const QVector2D rightPos(origin.x() + xoffsets[colInd + 1], origin.y() + yoffsets[rowInd]);
                const QPoint screenRightPos = m_camera->worldToScreen(rightPos);
                minDist = qAbs(qMin(minDist, screenRightPos.x() - screenCurPos.x()));
            }

            if (rowInd < yoffsets.size() - 1) {
                const QVector2D botPos(origin.x() + xoffsets[colInd], origin.y() + yoffsets[rowInd + 1]);
                const QPoint screenBotPos = m_camera->worldToScreen(botPos);
                minDist = qAbs(qMin(minDist, screenBotPos.y() - screenCurPos.y()));
            }

        }
    }

    const int fontSize = qMax(1.0f, qMin(0.2f * minDist, 15.0f));
    QFont font;
    font.setPixelSize(fontSize);
    painter.setFont(font);
    const QVector<QVector2D> positions = m_solverGLData->positions();

    for (int i = 0; i < positions.size(); i++){
        const QPoint screenPos = m_camera->worldToScreen(positions[i]);
        const QString strWorldPos = "(" + QString::number(positions[i].x()) + ", " + QString::number(positions[i].y()) + ")";
        //const QString strTemperature = " t = " + QString::number(m_solver->temperatures()[i]) + " K";
        const QString strCoefK = "K(x, y) = (" + QString::number(m_solver->coefX()[i]) + ", " + QString::number(m_solver->coefY()[i]) + ")";
        painter.drawText(screenPos + QPoint(3, -6 - 2 * fontSize), strWorldPos);
       // painter.drawText(screenPos + QPoint(3, -6 - fontSize), strTemperature);
        painter.drawText(screenPos + QPoint(3, -6 - fontSize), strCoefK);
    }
}

bool OpenGLWidget::isDrawOverlay() const
{
    return m_isDrawOverlay;
}

void OpenGLWidget::toggleOverlay()
{
    m_isDrawOverlay = !m_isDrawOverlay;
    update();
}
