#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QWidget>
#include <QVector>
#include <QOpenGLBuffer>
#include <QOpenGLWidget>
#include <QtMath>

#include "ObjectToDraw/objecttodraw.h"
#include "Camera/camera.h"

class Viewport : public QOpenGLWidget
{
    Q_OBJECT

public:
    Viewport(QWidget *parent = nullptr);
    ~Viewport();
    void addObject(ObjectToDraw *objectToDraw);
    void clear();
    void editColorCurrentObject();
    void cameraToOrigin();
    QVector3D cameraTransfer();
    QVector3D cameraScale();
    ObjectToDraw* findNearestObject(const QVector3D &point);

protected:
    void initializeGL() override;
    void resizeGL(qint32 width, qint32 height) override;
    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    // TO DELETE
    void scaleCurrentObjectWithKeys(const Qt::Key &keyPress);
    void shiftCurrentObjectWithKeys(const Qt::Key &keyPress);

    Camera *m_camera = new Camera();
    QVector<ObjectToDraw *> m_ObjectsToDraw;

    ObjectToDraw *m_currentObject = nullptr;
    QColor m_colorCurrentObject;

    QColor m_backgroundColor = QColor(87, 93, 94);
    qreal m_selectionRadius = 10;
    qreal m_NormalTransferSpeed = 10;
    qreal m_NormalRotateSpeed = M_PI_4/50;
    qreal m_NormalScaleSpeed = 1e-3f;
    qreal m_wheelSpeed = 1e-3f;

    QPointF m_oldMousePosition;
};
#endif // VIEWPORT_H
