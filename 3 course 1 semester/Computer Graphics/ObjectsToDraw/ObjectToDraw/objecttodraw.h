#ifndef OBJECTTODRAW_H
#define OBJECTTODRAW_H

#include <QColor>
#include <QVector3D>
#include <QMatrix4x4>

class ObjectToDraw
{
public:
    ObjectToDraw();
    virtual void draw(const QMatrix4x4 &viewMatrix, const QMatrix4x4 &clipMatrix) = 0;

    virtual void scale(const QVector3D &scale) = 0;
    virtual void shift(const QVector3D &shift) = 0; // сдвиг на
    virtual void shiftTo(const QVector3D &shift) = 0; // сдвиг в точку

    virtual void transforamtion(QMatrix4x4 transformMatrix);

    virtual qreal findDistanceToObject(const QVector3D &point, const QMatrix4x4 &viewMatrix) = 0;
    virtual bool pointInsideObject(const QVector3D &point) = 0;

    virtual void setColor(const QColor &color);
    virtual QColor getColor();

    virtual void vertexScaling(const QVector3D &scale) {Q_UNUSED(scale)};
    virtual void reflection() {};

    virtual void rotation(qreal angel){Q_UNUSED(angel)};
protected:
    QColor m_color;
    QMatrix4x4 m_modelMatrix;
};

#endif // OBJECTTODRAW_H
