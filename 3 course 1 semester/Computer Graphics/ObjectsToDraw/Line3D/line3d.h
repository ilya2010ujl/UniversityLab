#ifndef LINE2D_H
#define LINE2D_H

#include <QVector4D>
#include <QColor>

#include "ObjectToDraw/objecttodraw.h"

class Line3D : public ObjectToDraw
{
public:
    Line3D(const QVector3D &begin, const QVector3D &end,
           const qreal &a_lineSize = 1,
           const QColor &color = QColorConstants::Yellow);
    void draw(const QMatrix4x4 &viewMatrix, const QMatrix4x4 &clipMatrix) override;

    void scale(const QVector3D &scale) override;
    void shift(const QVector3D &shift) override; // сдвиг на
    void shiftTo(const QVector3D &shift) override; // сдвиг в точку

    qreal findDistanceToObject(const QVector3D &point, const QMatrix4x4 &viewMatrix) override;
    bool pointInsideObject(const QVector3D &point) override;
private:
    QVector4D m_begin;
    QVector4D m_end;
    qreal m_lineSize;
};

#endif // LINE2D_H
