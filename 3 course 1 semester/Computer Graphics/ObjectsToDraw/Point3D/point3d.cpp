#include <QtOpenGL>

#include "point3d.h"

#define DEBUG

Point3D::Point3D(const QVector3D &a_point, const qreal &a_pointSize, const QColor &a_color)
    : ObjectToDraw(), m_pointSize(a_pointSize)
{
    m_point = QVector4D(a_point, 1);
    m_color = a_color;
}

void Point3D::draw(const QMatrix4x4 &viewMatrix, const QMatrix4x4 &clipMatrix)
{
     QVector4D point = clipMatrix * viewMatrix * m_point;

    glPointSize(m_pointSize);

    glBegin(GL_POINTS);
       glColor3d(m_color.redF(), m_color.greenF(), m_color.blueF());
       glVertex3d(point.x(), point.y(), point.z());
    glEnd();
}

void Point3D::scale(const QVector3D &scale)
{
    // Q_UNUSED(scale);

    m_pointSize *= (1 + scale.x());
}

void Point3D::shift(const QVector3D &shift)
{
    m_point += QVector4D(shift, 0);
}

void Point3D::shiftTo(const QVector3D &shift)
{
    m_point = QVector4D(0,0,0,0);
    this->shift(shift);
}

qreal Point3D::findDistanceToObject(const QVector3D &point, const QMatrix4x4 &viewMatrix)
{
#ifdef DEBUG
        qDebug() << "Point3D::findDistanceToObject:\n"
                 << "\tpoint: " << m_point << '\n'
                 << "\tclicl: " << point << '\n';
#endif
    return (m_point - QVector4D(point,1)).length();
}

bool Point3D::pointInsideObject(const QVector3D &point)
{
    Q_UNUSED(point);

    return false;
}
