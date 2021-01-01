#include <limits>
#include <QDebug>
#include "modeltodraw.h"
#include "Camera/camera.h"
#include <QtMath>

#define DEBUG

ModelToDraw::ModelToDraw(QVector<qreal> vertex, QVector<qreal> normals, QVector<qreal> color, quint64 size)
{
    m_vertex.resize(size);
    m_color.resize(size);
    m_normals.resize(size);

    for(quint64 i = 0; i < size; ++i)
    {
        m_vertex[i] = QVector4D(vertex[3 * i + 0],
                vertex[3 * i + 1],
                vertex[3 * i + 2], 1);

        m_normals[i] = QVector4D(normals[3 * i + 0],
                normals[3 * i + 1],
                normals[3 * i + 2], 1);
        m_color[i] = QVector4D(color[3 * i + 0],
                color[3 * i + 1],
                color[3 * i + 2], 1);
    }
}

void ModelToDraw::draw(const QMatrix4x4 &viewMatrix, const QMatrix4x4 &clipMatrix)
{
    int size = m_vertex.size();

    QVector4D v1, v2, v3;

    QMatrix4x4 matrix = clipMatrix * viewMatrix * m_modelMatrix;

    glBegin(GL_TRIANGLES);
    for(int i = 0; i < size / 3; ++i)
    {
        v1 = matrix * m_vertex[3 * i + 0];
        v2 = matrix * m_vertex[3 * i + 1];
        v3 = matrix * m_vertex[3 * i + 2];

        glColor3d(m_color[3 * i + 0].x(),m_color[3 * i + 0].y(),m_color[3 * i + 0].z());
        glVertex3d(v1.x(),v1.y(),v1.z());
        glColor3d(m_color[3 * i + 1].x(),m_color[3 * i + 1].y(),m_color[3 * i + 1].z());
        glVertex3d(v2.x(),v2.y(),v2.z());
        glColor3d(m_color[3 * i + 2].x(),m_color[3 * i + 2].y(),m_color[3 * i + 2].z());
        glVertex3d(v3.x(),v3.y(),v3.z());
    }
    glEnd();
}

void ModelToDraw::scale(const QVector3D &scale)
{
    // лень деать новые шорткаты, тупо заменю старые
    // да простит меня бог

    for(int i = 0; i < 3; ++i)
    {
        this->m_modelMatrix(i,i) += scale[i];
    }
}

void ModelToDraw::shift(const QVector3D &shift)
{
    for(int i = 0; i < 3; ++i)
    {
        this->m_modelMatrix(i,3) += shift[i];
    }
}

void ModelToDraw::shiftTo(const QVector3D &shift)
{
    for(int i = 0; i < 3; ++i)
    {
        this->m_modelMatrix(i,3) = shift[i];
    }
}

qreal ModelToDraw::findDistanceToObject(const QVector3D &point, const QMatrix4x4 &viewMatrix)
{
    Q_UNUSED(viewMatrix);

    qreal result = std::numeric_limits<qreal>::max(), distance;

    for(int i = 0; i < m_vertex.size(); ++i)
    {
        distance = (point - m_modelMatrix * m_vertex[i]).length();
        if(distance < result)
        {
            result = distance;
        }
    }

    return result;
}

bool ModelToDraw::pointInsideObject(const QVector3D &point)
{
    Q_UNUSED(point);
    return false;
}

void ModelToDraw::vertexScaling(const QVector3D &scale)
{
    // scale относительно вершины и модели разные скейлы
    QVector4D v = m_vertex[1];

    QMatrix4x4 T = Camera::transferMatrix(QVector3D(-v.x(), -v.y(), -v.z()));
    QMatrix4x4 _T = Camera::transferMatrix(QVector3D(v.x(), v.y(), v.z()));

    QMatrix4x4 S;

    for(int i = 0; i < 3; ++i)
    {
        S(i,i) += scale[i];
    }

    m_modelMatrix = m_modelMatrix * _T * S * T;
}

void ModelToDraw::reflection()
{
    QVector4D v1 = m_vertex[1], v2 = m_vertex[2];

#ifdef DEBUG
   qDebug() << v1 << v2;
#endif

    QMatrix4x4 T = Camera::transferMatrix(QVector3D(-v1.x(), -v1.y(), -v1.z()));
    QMatrix4x4 _T = Camera::transferMatrix(QVector3D(v1.x(), v1.y(), v1.z()));

    QVector3D v23D(T * v2);
    v23D.normalize();
    qreal cosinus = QVector3D::dotProduct(v23D, QVector3D(1,0,0));

    qreal angel = qAcos(cosinus);

    if(v23D.y() < 0)
    {
        angel *= -1;
    }

    QMatrix4x4 R = Camera::rotateMatrix(-angel);
    QMatrix4x4 _R = Camera::rotateMatrix(angel);

    QMatrix4x4 S = Camera::scaleMatrix(QVector3D(1,-1,1));

    m_modelMatrix = m_modelMatrix * _T * _R * S * R  * T;
}

void ModelToDraw::rotation(qreal angle)
{
//    QVector4D sum;

//    quint64 size = m_vertex.size();

//    for(quint64 i = 0; i < size; ++i)
//    {
//        sum += m_vertex[i];
//    }

//    sum /= size;

//    QMatrix4x4 T = Camera::transferMatrix(-QVector3D(sum));
//    QMatrix4x4 _T = Camera::transferMatrix(QVector3D(sum));

    this->m_modelMatrix = Camera::rotateMatrix(angle) * this->m_modelMatrix;
}
