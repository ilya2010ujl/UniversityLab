#ifndef DISCRETEFUNCTION_H
#define DISCRETEFUNCTION_H

#include <QVector4D>

#include "ObjectToDraw/objecttodraw.h"

class DiscreteFunction : public ObjectToDraw
{
public:
    DiscreteFunction(const QVector<QVector2D>& a_points);

    virtual void draw(const QMatrix4x4 &viewMatrix) override;
private:
    QVector<QVector2D> m_points;
};

#endif // DISCRETEFUNCTION_H
