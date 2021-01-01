#include <QtOpenGL>

#include "line3d.h"
#include "Utils/utils.h"

Line3D::Line3D(const QVector3D &begin, const QVector3D &end,
               const qreal &a_lineSize, const QColor &color)
    : ObjectToDraw(), m_begin(begin, 1), m_end(end, 1), m_lineSize(a_lineSize)
{
    QVector3D center = (begin + end)/2;
    m_begin -= center;
    m_end -= center;
    shift(center);

    this->m_color = color;
}

void Line3D::draw(const QMatrix4x4 &viewMatrix, const QMatrix4x4 &clipMatrix)
{
    QVector4D begin = clipMatrix * viewMatrix * m_modelMatrix * m_begin;
    QVector4D end = clipMatrix * viewMatrix * m_modelMatrix * m_end;

    glLineWidth(m_lineSize);

    glBegin(GL_LINES);
        glColor3d(m_color.redF(), m_color.greenF(), m_color.blueF());
        glVertex3d(begin.x(), begin.y(), begin.z());
        glVertex3d(end.x(), end.y(), end.z());
    glEnd();
}

void Line3D::scale(const QVector3D &scale)
{
    // m_lineSize *= (1 + scale.x());

    for(int i = 0; i < 3; ++i)
    {
        this->m_modelMatrix(i,i) += scale[i];
    }
}

void Line3D::shift(const QVector3D &shift)
{
    for(int i = 0; i < 3; ++i)
    {
        this->m_modelMatrix(i,3) += shift[i];
    }
}

void Line3D::shiftTo(const QVector3D &shift)
{
    for(int i = 0; i < 3; ++i)
    {
        this->m_modelMatrix(i,3) = shift[i];
    }
}

qreal Line3D::findDistanceToObject(const QVector3D &point, const QMatrix4x4 &viewMatrix)
{
    QVector3D begin = QVector3D(m_modelMatrix * m_begin);
    QVector3D end = QVector3D(m_modelMatrix * m_end);

    return utils::distanceFromPointToLineSegment(point, begin, end);
}

bool Line3D::pointInsideObject(const QVector3D &point)
{
    Q_UNUSED(point)
    return false;
}
