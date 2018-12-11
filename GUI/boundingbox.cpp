#include "boundingbox.h"

BoundingBox::BoundingBox()
    : m_min(QVector2D(std::numeric_limits<float>::max(), std::numeric_limits<float>::max())),
      m_max(QVector2D(std::numeric_limits<float>::min(), std::numeric_limits<float>::min()))
{

}

BoundingBox::BoundingBox(const QVector<QVector2D> &positions)
{
    QVector2D min(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    QVector2D max(std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
    for (int i = 0; i < positions.size(); i++) {
        const QVector2D &pos = positions[i];
        if (min.x() > pos.x())
            min.setX(pos.x());
        if (min.y() > pos.y())
            min.setY(pos.y());

        if (max.x() < pos.x())
            max.setX(pos.x());
        if (max.y() < pos.y())
            max.setY(pos.y());
    }

    m_min = min;
    m_max = max;
}

bool BoundingBox::isValid() const {
    return m_max.x() >= m_min.x() && m_max.y() >= m_min.y();
}
