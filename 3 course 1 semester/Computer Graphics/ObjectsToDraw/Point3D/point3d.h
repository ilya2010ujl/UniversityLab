#ifndef POINT_H
#define POINT_H

#include <QColor>
#include <QVector4D>

#include "ObjectToDraw/objecttodraw.h"

class Point3D : public ObjectToDraw
{
public:
    Point3D(const QVector3D &a_point, const qreal &a_pointSize = 5, const QColor &m_color = QColorConstants::White);
    void draw(const QMatrix4x4 &viewMatrix, const QMatrix4x4 &clipMatrix) override;

    void scale(const QVector3D &scale) override;
    void shift(const QVector3D &shift) override; // сдвиг на
    void shiftTo(const QVector3D &shift) override; // сдвиг в точку

    qreal findDistanceToObject(const QVector3D &point, const QMatrix4x4 &viewMatrix) override;
    bool pointInsideObject(const QVector3D &point) override;
private:
    QVector4D m_point;
    qreal  m_pointSize;
};

#endif // POINT_H
