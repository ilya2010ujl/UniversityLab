#include <limits>
#include <QColor>

#include "explicitgraphoffunction.h"

ExplicitGraphOfFunction::ExplicitGraphOfFunction(const ExplicitGraphOfFunction::Function &a_y_x,
                                                 Viewport *a_viewport, qreal a_step)
    : m_y_x(a_y_x), m_viewport(a_viewport), m_step(a_step)
{
    this->m_color = QColorConstants::Magenta;
}

void ExplicitGraphOfFunction::draw(const QMatrix4x4 &viewMatrix, const QMatrix4x4 &clipMatrix)
{
    qreal width = m_viewport->geometry().width();

    QVector3D transfer = m_viewport->cameraTransfer();
    QVector3D scale = m_viewport->cameraScale();

    int L = (- width/2. - transfer.x() - 700) * (1 / scale.x());
    int R = (  width/2. - transfer.x() + 700) * (1 / scale.x());

    QVector4D begin, end;

    glColor3f(m_color.redF(), m_color.greenF(), m_color.blueF());
    glLineWidth(2);
    glBegin(GL_LINES);
        for(qreal i = L; i < R; i += m_step)
        {
            begin = QVector4D(50 * i,  50 * m_y_x(i), 0, 1);
            end = QVector4D(50 * (i + m_step), 50 * m_y_x(i + m_step), 0, 1);

            begin = clipMatrix * viewMatrix * begin;
            end = clipMatrix * viewMatrix * end;

            glVertex3f(begin.x(), begin.y(), 0);
            glVertex3f(end.x(), end.y(), 0);
        }
    glEnd();
}

void ExplicitGraphOfFunction::scale(const QVector3D &scale)
{
    Q_UNUSED(scale)
}

void ExplicitGraphOfFunction::shift(const QVector3D &shift)
{
    Q_UNUSED(shift)
}

void ExplicitGraphOfFunction::shiftTo(const QVector3D &shift)
{
    Q_UNUSED(shift)
}

qreal ExplicitGraphOfFunction::findDistanceToObject(const QVector3D &point, const QMatrix4x4 &viewMatrix)
{
    Q_UNUSED(point)
    Q_UNUSED(viewMatrix)

    return std::numeric_limits<qreal>::max();
}

bool ExplicitGraphOfFunction::pointInsideObject(const QVector3D &point)
{
    Q_UNUSED(point)

    return false;
}
