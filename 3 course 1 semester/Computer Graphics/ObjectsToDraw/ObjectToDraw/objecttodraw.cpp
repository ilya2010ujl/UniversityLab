#include "objecttodraw.h"

ObjectToDraw::ObjectToDraw()
{
    m_modelMatrix.setToIdentity();
}

void ObjectToDraw::transforamtion(QMatrix4x4 transformMatrix)
{
    m_modelMatrix = transformMatrix * m_modelMatrix;
}

void ObjectToDraw::setColor(const QColor &color)
{
    m_color = color;
}

QColor ObjectToDraw::getColor()
{
    return m_color;
}
