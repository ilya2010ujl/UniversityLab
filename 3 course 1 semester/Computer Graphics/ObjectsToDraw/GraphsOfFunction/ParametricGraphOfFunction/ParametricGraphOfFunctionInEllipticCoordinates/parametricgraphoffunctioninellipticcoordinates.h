#ifndef PARAMETRICGRAPHOFFUNCTIONINELLIPTICCOORDINATES_H
#define PARAMETRICGRAPHOFFUNCTIONINELLIPTICCOORDINATES_H

#include <QColor>
#include <QVector4D>

#include "ObjectToDraw/objecttodraw.h"
#include "Viewport/viewport.h"

class ParametricGraphOfFunctionInEllipticCoordinates : public ObjectToDraw
{
public:
    using Function = std::function<qreal(const qreal &)>;

    ParametricGraphOfFunctionInEllipticCoordinates(const Function &a_mu_t, const Function &a_v_t,
                                                   const qreal &a_focus, const qreal &a_t_min, const qreal &a_t_max,
                                                   Viewport *a_viewport, const qreal &a_step);

    virtual void draw(const QMatrix4x4 &viewMatrix, const QMatrix4x4 &clipMatrix) override;

    virtual void scale(const QVector3D &scale) override;
    virtual void shift(const QVector3D &shift) override; // сдвиг на
    virtual void shiftTo(const QVector3D &shift) override; // сдвиг в точку

    virtual qreal findDistanceToObject(const QVector3D &point, const QMatrix4x4 &viewMatrix) override;
    virtual bool pointInsideObject(const QVector3D &point) override;

    static qreal sh(const qreal &t);
    static qreal ch(const qreal &t);

private:
    Viewport *m_viewport;
    qreal m_step;
    Function m_mu_t;
    Function m_v_t;
    qreal m_focus;
    qreal m_t_min;
    qreal m_t_max;

    qreal x(const qreal &t);
    qreal y(const qreal &t);
};

#endif // PARAMETRICGRAPHOFFUNCTIONINELLIPTICCOORDINATES_H
