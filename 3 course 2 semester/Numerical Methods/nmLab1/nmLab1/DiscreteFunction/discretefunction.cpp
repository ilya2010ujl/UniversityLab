#include <QColor>
#include <QOpenGLFunctions>

#include "discretefunction.h"

#define DEBUG

DiscreteFunction::DiscreteFunction(const QVector<QVector2D> &a_points) : m_points(a_points) {}

void DiscreteFunction::draw(const QMatrix4x4 &viewMatrix)
{
    glColor3f(m_color.redF(), m_color.greenF(), m_color.blueF());

    QVector4D begin, end;
    QMatrix4x4 drawMatrix = viewMatrix * m_modelMatrix;

    glLineWidth(3);

    int size = m_points.size();

    glBegin(GL_LINES);

    for(int i = 1; i < size; ++i)
    {
        begin = drawMatrix * QVector4D(m_points[i - 1], 0, 1);

        end = drawMatrix * QVector4D(m_points[i], 0, 1);

        glVertex3f(begin.x(), begin.y(), 0);
        glVertex3f(end.x(), end.y(), 0);
    }

    glEnd();
}
