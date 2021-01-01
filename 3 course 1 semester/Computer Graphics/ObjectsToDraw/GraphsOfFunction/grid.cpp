#include <limits>

#include "grid.h"

Grid::Grid(Viewport *a_viewport) : m_viewport(a_viewport)
{
    this->m_color = QColorConstants::Gray;
}

void Grid::draw(const QMatrix4x4 &viewMatrix, const QMatrix4x4 &clipMatrix)
{
    qreal width = m_viewport->geometry().width();
    qreal height = m_viewport->geometry().height();

    QVector3D transfer = m_viewport->cameraTransfer();
    QVector3D scale = m_viewport->cameraScale();

    int L = (- width/2. - transfer.x() - 700) * (1 / scale.x());
    int R = (  width/2. - transfer.x() + 700) * (1 / scale.x());

    int T = (  height / 2. - transfer.y() + 700) * (1 / scale.y());
    int B = (- height / 2. - transfer.y() - 700) * (1 / scale.y());

    glColor3f(m_color.redF(), m_color.greenF(), m_color.blueF());

    glLineWidth(3);
    glBegin(GL_LINES);
        QVector4D point;

        point = QVector4D(0, T, 0, 1);
        point = clipMatrix * viewMatrix * point;
        glVertex3f(point.x(), point.y(), point.z());

        point = QVector4D(0, B, 0, 1);
        point = clipMatrix * viewMatrix * point;
        glVertex3f(point.x(), point.y(), point.z());

        point = QVector4D(L, 0, 0, 1);
        point = clipMatrix * viewMatrix * point;
        glVertex3f(point.x(), point.y(), point.z());

        point = QVector4D(R, 0, 0, 1);
        point = clipMatrix * viewMatrix * point;
        glVertex3f(point.x(), point.y(), point.z());
    glEnd();


    QVector4D begin, end;
    glLineWidth(1);
    glBegin(GL_LINES);

        int tmp = L;

        while(tmp < R)
        {
            tmp = (tmp / 50) * 50;

            begin = QVector4D(tmp, T, 0, 1);
            end = QVector4D(tmp, B, 0, 1);

            begin = clipMatrix * viewMatrix * begin;
            end = clipMatrix * viewMatrix * end;

            glVertex3f(begin.x(), begin.y(), 0);
            glVertex3f(end.x(), end.y(), 0);

            tmp += 50;
        }

        tmp = B;

        while(tmp < T)
        {
            tmp = (tmp / 50) * 50;

            begin = QVector4D(L, tmp, 0, 1);
            end = QVector4D(R, tmp, 0, 1);

            begin = clipMatrix * viewMatrix * begin;
            end = clipMatrix * viewMatrix * end;

            glVertex3f(begin.x(), begin.y(), 0);
            glVertex3f(end.x(), end.y(), 0);

            tmp += 50;
        }
    glEnd();
}

void Grid::scale(const QVector3D &scale)
{
    Q_UNUSED(scale)
}

void Grid::shift(const QVector3D &shift)
{
    Q_UNUSED(shift)
}

void Grid::shiftTo(const QVector3D &shift)
{
    Q_UNUSED(shift)
}

qreal Grid::findDistanceToObject(const QVector3D &point, const QMatrix4x4 &viewMatrix)
{
    Q_UNUSED(point)
    Q_UNUSED(viewMatrix)

    return std::numeric_limits<qreal>::max();
}

bool Grid::pointInsideObject(const QVector3D &point)
{
    Q_UNUSED(point)

    return false;
}

