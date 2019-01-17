#ifndef CAMERA_H
#define CAMERA_H

#include "boundingbox.h"
#include <QVector2D>
#include <QMatrix4x4>

class Camera
{
public:
    Camera() : m_zoom(1) { }

    void move(int dx, int dy, double speed);
    void zoom(int delta);

    void fitToScreen(const BoundingBox &boundingBox);
    void resize(int width, int height);
    QMatrix4x4 projection() const;
    QMatrix4x4 view() const;
    QPoint worldToScreen(const QVector2D &worldPos) const;

private:
    QVector2D m_position;
    double m_zoom;
    int m_width;
    int m_height;

    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;
};


inline QMatrix4x4 Camera::projection() const {
    return m_projection;
}

inline QMatrix4x4 Camera::view() const {
    return m_view;
}


#endif // CAMERA_H
