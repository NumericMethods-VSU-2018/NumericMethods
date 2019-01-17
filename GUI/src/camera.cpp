#include "camera.h"


#include <QtMath>
#include <QVector4D>

void Camera::move(int dx, int dy, double speed) {
    const QVector2D delta(speed * dx, -speed * dy);
    m_position -= delta;
    m_view.translate(delta);
}

void Camera::zoom(int delta) {
    m_zoom *= delta > 0? 1.1f: 0.9f;

    m_view.setToIdentity();
    m_view.scale(m_zoom);
    m_view.translate(-m_position);
}

void Camera::fitToScreen(const BoundingBox &boundingBox)
{
    const QVector2D &diag = boundingBox.diag();
    m_zoom = diag.x() > diag.y() ? 0.95f * m_width / diag.x() : 0.95f * m_height / diag.y();
    m_position = boundingBox.mid();

    m_view.setToIdentity();
    m_view.scale(m_zoom);
    m_view.translate(-m_position);
}

void Camera::resize(int width, int height) {
    QMatrix4x4 proj;
    double right = width / 2;
    double left = -right;
    double top = height / 2;
    double bottom = -top;
    double far = 1;
    double near = -1;
    proj.ortho(left, right, bottom, top, near, far);

    m_width = width;
    m_height = height;
    m_projection = proj;
}

QPoint Camera::worldToScreen(const QVector2D &worldPos) const
{
    const QVector4D projectionPos = m_projection * m_view * QVector4D(worldPos, 0.0f, 1.0f);
    const QPoint screenPos(m_width * (projectionPos.x() + 1) / 2, m_height * (1 - (projectionPos.y() + 1) / 2) );
    return screenPos;
}
