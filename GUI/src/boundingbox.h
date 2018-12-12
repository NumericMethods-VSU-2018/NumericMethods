#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <QVector2D>
#include <QVector>

class BoundingBox
{
public:
    BoundingBox();
    BoundingBox(const QVector<QVector2D> &positions);

    QVector2D diag() const;
    QVector2D mid() const;
    QVector2D min() const;
    QVector2D max() const;
    bool isValid() const;
private:
    QVector2D m_min;
    QVector2D m_max;
};

inline QVector2D BoundingBox::diag() const{
    return m_max - m_min;
}
inline QVector2D BoundingBox::mid() const{
    return (m_max + m_min) / 2;
}
inline QVector2D BoundingBox::min() const{
    return m_min;
}
inline QVector2D BoundingBox::max() const{
    return m_max;
}
#endif // BOUNDINGBOX_H
