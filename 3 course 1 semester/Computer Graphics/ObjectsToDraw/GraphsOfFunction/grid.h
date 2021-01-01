#ifndef GRID_H
#define GRID_H

#include "ObjectToDraw/objecttodraw.h"
#include "Viewport/viewport.h"

class Grid : public ObjectToDraw
{
public:
    using Function = std::function<qreal(const qreal &)>;

    Grid(Viewport *a_viewport);

    virtual void draw(const QMatrix4x4 &viewMatrix, const QMatrix4x4 &clipMatrix) override;

    virtual void scale(const QVector3D &scale) override;
    virtual void shift(const QVector3D &shift) override; // сдвиг на
    virtual void shiftTo(const QVector3D &shift) override; // сдвиг в точку

    virtual qreal findDistanceToObject(const QVector3D &point, const QMatrix4x4 &viewMatrix) override;
    virtual bool pointInsideObject(const QVector3D &point) override;

private:
    Viewport *m_viewport;
};

#endif // PARAMETRICGRAPHOFFUNCTION_H
