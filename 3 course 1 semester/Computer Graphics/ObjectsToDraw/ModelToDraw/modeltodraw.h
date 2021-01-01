#ifndef MODELTODRAW_H
#define MODELTODRAW_H

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector4D>
#include "ObjectToDraw/objecttodraw.h"

class ModelToDraw : public ObjectToDraw
{
public:
    ModelToDraw(QVector<qreal> vertex, QVector<qreal> normals, QVector<qreal> color, quint64 size);
    void draw(const QMatrix4x4 &viewMatrix, const QMatrix4x4 &clipMatrix) override;

    void scale(const QVector3D &scale) override;
    void shift(const QVector3D &shift) override; // сдвиг на
    void shiftTo(const QVector3D &shift) override; // сдвиг в точку

    qreal findDistanceToObject(const QVector3D &point, const QMatrix4x4 &viewMatrix) override;
    bool pointInsideObject(const QVector3D &point) override;

    void vertexScaling(const QVector3D &scale) override;
    void reflection() override;

    void rotation(qreal angle) override;
private:
    QVector<QVector4D> m_vertex;
    QVector<QVector4D> m_normals;
    QVector<QVector4D> m_color;
};

#endif // OBJECTTODRAW_H
