#include <QtMath>

#include "camera.h"

#define DEBUG

Camera::Camera(const qreal &a_width, const qreal &a_hight) : m_width(a_width), m_hight(a_hight) {}

void Camera::rotation(const qreal &a_rotate)
{
    m_rotate += a_rotate;
}

void Camera::transferring(const QVector3D &a_transfer)
{
    m_transfer += a_transfer;
}

void Camera::scaling(const QVector3D &a_scale)
{
    m_scale += a_scale;
}

QMatrix4x4 Camera::viewMatrix()
{
    QMatrix4x4 rotateMatrix = Camera::rotateMatrix(m_rotate);
    QMatrix4x4 transferMatrix = Camera::transferMatrix(m_transfer);
    QMatrix4x4 scaleMatrix = Camera::scaleMatrix(QVector3D(m_scale.x(), m_scale.y(), 1));

    QMatrix4x4 viewMatrix = transferMatrix * rotateMatrix * scaleMatrix;

    return viewMatrix;
}

QMatrix4x4 Camera::clipMatrix()
{
    QMatrix4x4 clipMatrix = scaleMatrix(QVector3D(2 / m_width, 2 / m_hight, 1));

    return clipMatrix;
}

QMatrix4x4 Camera::rotateMatrix(const qreal &angel)
{
    QMatrix4x4 Rotate;

    Rotate(0,0) = qCos(angel);
    Rotate(0,1) = -qSin(angel);

    Rotate(1,0) = qSin(angel);
    Rotate(1,1) = qCos(angel);

    return Rotate;
}

QMatrix4x4 Camera::transferMatrix(const QVector3D &transfer)
{
    QMatrix4x4 Transfer;

    for(int i = 0; i < 3; ++i)
    {
        Transfer(i, 3) = transfer[i];
    }

    return Transfer;
}

QMatrix4x4 Camera::scaleMatrix(const QVector3D &scale)
{
    QMatrix4x4 Scale;

    for(int i = 0; i < 3; ++i)
    {
        Scale(i, i) = scale[i];
    }

    return Scale;
}

qreal Camera::width() const
{
    return m_width;
}

void Camera::setWidth(const qreal &width)
{
    m_width = width;
}

qreal Camera::hight() const
{
    return m_hight;
}

void Camera::setHight(const qreal &hight)
{
    m_hight = hight;
}

QPointF Camera::ScreenToWorld(const QPointF &screenCoord)
{
    QMatrix4x4 rotateMatrix = Camera::rotateMatrix(-m_rotate);
    QMatrix4x4 transferMatrix = Camera::transferMatrix(-m_transfer);
    QMatrix4x4 scaleMatrix = Camera::scaleMatrix(QVector3D(1 / m_scale.x(), 1 / m_scale.y(), 1 / m_scale.z()));

    QMatrix4x4 viewMatrix = scaleMatrix * rotateMatrix * transferMatrix;

    QVector4D word( - m_width / 2 + screenCoord.x(), m_hight / 2 - screenCoord.y(), 0, 1);

    word = viewMatrix * word;

    return QPointF( word.x(), word.y());
}

QVector3D Camera::scale() const
{
    return m_scale;
}

void Camera::setScale(const QVector3D &scale)
{
    m_scale = scale;
}

void Camera::toOrigin()
{
    m_transfer = QVector3D(0,0,0);
    m_scale = QVector3D(1,1,1);
    m_rotate = 0;
}

QVector3D Camera::transfer() const
{
    return m_transfer;
}

void Camera::setTransfer(const QVector3D &transfer)
{
    m_transfer = transfer;
}
