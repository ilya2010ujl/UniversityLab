#ifndef EPLICITGRAPHOFFUNCTION_H
#define EPLICITGRAPHOFFUNCTION_H

#include <QVector4D>

#include "ObjectToDraw/objecttodraw.h"
#include "Viewport/viewport.h"

class ExplicitGraphOfFunction : public ObjectToDraw
{
public:
    using Function = std::function<qreal(const qreal &)>;

    ExplicitGraphOfFunction(const Function &a_y_x, Viewport *a_viewport, qreal a_step);

    virtual void draw(const QMatrix4x4 &viewMatrix, const QMatrix4x4 &clipMatrix) override;

    virtual void scale(const QVector3D &scale) override;
    virtual void shift(const QVector3D &shift) override; // сдвиг на
    virtual void shiftTo(const QVector3D &shift) override; // сдвиг в точку

    virtual qreal findDistanceToObject(const QVector3D &point, const QMatrix4x4 &viewMatrix) override;
    virtual bool pointInsideObject(const QVector3D &point) override;

private:
    Function m_y_x;
    Viewport *m_viewport;
    qreal m_step;
};

#endif // EPLICITGRAPHOFFUNCTION_H
