#include <limits>
#include <QtMath>

#include "parametricgraphoffunctioninellipticcoordinates.h"

ParametricGraphOfFunctionInEllipticCoordinates::ParametricGraphOfFunctionInEllipticCoordinates
(const ParametricGraphOfFunctionInEllipticCoordinates::Function &a_mu_t,
 const ParametricGraphOfFunctionInEllipticCoordinates::Function &a_v_t,
 const qreal &a_focus,
 const qreal &a_t_min, const qreal &a_t_max,
 Viewport *a_viewport, const qreal &a_step)
: m_viewport(a_viewport), m_step(a_step), m_mu_t(a_mu_t), m_v_t(a_v_t), m_focus(a_focus),
  m_t_min(a_t_min), m_t_max(a_t_max)
{
    this->m_color = QColorConstants::Magenta;
}

void ParametricGraphOfFunctionInEllipticCoordinates::draw(const QMatrix4x4 &viewMatrix,
                                                          const QMatrix4x4 &clipMatrix)
{
    QVector4D begin, end;

    glColor3f(m_color.redF(), m_color.greenF(), m_color.blueF());
    glLineWidth(2);
    glBegin(GL_LINES);
        qreal t = m_t_min;
        for(; t < m_t_max - m_step; t += m_step)
        {
            begin = QVector4D(50 * x(t),  50 * y(t), 0, 1);
            end = QVector4D(50 * x(t + m_step), 50 * y(t + m_step), 0, 1);

            begin = clipMatrix * viewMatrix * begin;
            end = clipMatrix * viewMatrix * end;

            glVertex3f(begin.x(), begin.y(), 0);
            glVertex3f(end.x(), end.y(), 0);
        }

        begin = QVector4D(50 * x(t),  50 * y(t), 0, 1);
        end = QVector4D(50 * x(m_t_max), 50 * y(m_t_max), 0, 1);

        begin = clipMatrix * viewMatrix * begin;
        end = clipMatrix * viewMatrix * end;

        glVertex3f(begin.x(), begin.y(), 0);
        glVertex3f(end.x(), end.y(), 0);
    glEnd();
}

void ParametricGraphOfFunctionInEllipticCoordinates::scale(const QVector3D &scale)
{
    Q_UNUSED(scale)
}

void ParametricGraphOfFunctionInEllipticCoordinates::shift(const QVector3D &shift)
{
    Q_UNUSED(shift)
}

void ParametricGraphOfFunctionInEllipticCoordinates::shiftTo(const QVector3D &shift)
{
    Q_UNUSED(shift)
}

qreal ParametricGraphOfFunctionInEllipticCoordinates::findDistanceToObject(const QVector3D &point,
                                                                           const QMatrix4x4 &viewMatrix)
{
    Q_UNUSED(point)
    Q_UNUSED(viewMatrix)

    return std::numeric_limits<qreal>::max();
}

bool ParametricGraphOfFunctionInEllipticCoordinates::pointInsideObject(const QVector3D &point)
{
    Q_UNUSED(point)

    return false;
}

qreal ParametricGraphOfFunctionInEllipticCoordinates::sh(const qreal &t)
{
    return (qExp(t) - qExp(-t)) / 2;
}

qreal ParametricGraphOfFunctionInEllipticCoordinates::ch(const qreal &t)
{
    return (qExp(t) + qExp(-t)) / 2;
}

qreal ParametricGraphOfFunctionInEllipticCoordinates::x(const qreal &t)
{
    return m_focus * ch(m_mu_t(t)) * qCos(m_v_t(t));
}

qreal ParametricGraphOfFunctionInEllipticCoordinates::y(const qreal &t)
{
    return m_focus * sh(m_mu_t(t)) * qSin(m_v_t(t));
}
