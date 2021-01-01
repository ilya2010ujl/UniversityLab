#include <limits>
#include <QKeyEvent>
#include <QDebug>
#include <QVector3D>
#include <QColorDialog>
#include <QtMath>

#include "viewport.h"
#include "grid.h"
#include "ExplicitGraphOfFunction/explicitgraphoffunction.h"
#include "ParametricGraphOfFunctionInEllipticCoordinates/parametricgraphoffunctioninellipticcoordinates.h"

#define DEBUG

Viewport::Viewport(QWidget *parent)
    : QOpenGLWidget(parent)
{
    Grid *grid = new Grid(this);
    this->addObject(grid);

    // TO DELETE
//    ExplicitGraphOfFunction *graph1 = new ExplicitGraphOfFunction(qExp, this, 0.1);
//    ExplicitGraphOfFunction *graph2 = new ExplicitGraphOfFunction(qLn, this, 0.1);

//    ParametricGraphOfFunctionInEllipticCoordinates
//            *graph3 = new ParametricGraphOfFunctionInEllipticCoordinates(
//    [](const qreal &t) -> qreal
//    {
//        Q_UNUSED(t)
//        return sin(t);
//    },
//    [](const qreal &t) -> qreal
//    {
//        Q_UNUSED(t)
//        return cos(t);
//    }, 1, 0, M_PI, this, 0.5);

//    this->addObject(graph1);
//    this->addObject(graph2);
//    this->addObject(graph3);
    // TO DELETE
}

Viewport::~Viewport() {}

void Viewport::addObject(ObjectToDraw *objectToDraw)
{
    m_ObjectsToDraw.push_back(objectToDraw);
}

void Viewport::clear()
{
    m_ObjectsToDraw.clear();
    Grid *grid = new Grid(this);
    this->addObject(grid);
}

void Viewport::editColorCurrentObject()
{
    if(m_currentObject)
    {
        m_colorCurrentObject = QColorDialog::getColor();
    }
}

void Viewport::cameraToOrigin()
{
    m_camera->toOrigin();
}

QVector3D Viewport::cameraTransfer()
{
    return m_camera->transfer();
}

QVector3D Viewport::cameraScale()
{
    return m_camera->scale();
}

ObjectToDraw *Viewport::findNearestObject(const QVector3D &point)
{
#ifdef DEBUG
    qDebug() << "Viewport::findNearestObject:";
#endif

    ObjectToDraw *result = nullptr;
    qreal distanceToResult = std::numeric_limits<qreal>::max();
    qreal distanceToObject;

    QMatrix4x4 viewMatrix = m_camera->viewMatrix();

    for (auto object: m_ObjectsToDraw)
    {
        if(object->pointInsideObject(point))
            return object;

        distanceToObject = object->findDistanceToObject(point, viewMatrix);
        if(distanceToObject < distanceToResult && distanceToObject < m_selectionRadius)
        {
            result = object;
            distanceToResult = distanceToObject;
        }
#ifdef DEBUG
        qDebug() << "\tselectionRadius: " << m_selectionRadius << '\n'
                 << "\tdistanceToObject: " << distanceToObject << '\n'
                 << "\tdistanceToResult: " << distanceToResult << '\n';
#endif
    }

    if(distanceToResult == std::numeric_limits<qreal>::max())
    {
        return nullptr;
    }

    return result;
}

void Viewport::initializeGL() {}

void Viewport::resizeGL(qint32 width, qint32 height)
{
#ifdef DEBUG
    qDebug() << "Viewport::resizeGL w: " << width << "h: " << height;
#endif

    m_camera->setHight(height);
    m_camera->setWidth(width);

    glViewport(0, 0, width, height);
}

void Viewport::paintGL()
{
    glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(),
                 m_backgroundColor.blueF(), m_backgroundColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto object: m_ObjectsToDraw)
    {
        object->draw(m_camera->viewMatrix(), m_camera->clipMatrix());
    }
}

void Viewport::keyPressEvent(QKeyEvent *event)
{
#ifdef DEBUG
    qDebug() << "Viewport::keyPressEvent " << event << "\n\tcamera::viewMatrix:\n" << m_camera->viewMatrix();
#endif

    switch(event->key())
    {
    // model
    case Qt::Key::Key_Left:
        shiftCurrentObjectWithKeys(Qt::Key::Key_Left);
        break;
    case Qt::Key::Key_Right:
        shiftCurrentObjectWithKeys(Qt::Key::Key_Right);
        break;
    case Qt::Key::Key_Up:
        shiftCurrentObjectWithKeys(Qt::Key::Key_Up);
        break;
    case Qt::Key::Key_Down:
        shiftCurrentObjectWithKeys(Qt::Key::Key_Down);
        break;

    case Qt::Key::Key_Plus:
        scaleCurrentObjectWithKeys(Qt::Key::Key_Plus);
        break;
    case Qt::Key::Key_Minus:
        scaleCurrentObjectWithKeys(Qt::Key::Key_Minus);
        break;

    // camera
    case Qt::Key::Key_W:
        m_camera->transferring(QVector3D(0, m_NormalTransferSpeed, 0));
        break;
    case Qt::Key::Key_S:
        m_camera->transferring(QVector3D(0, -m_NormalTransferSpeed, 0));
        break;
    case Qt::Key::Key_A:
        m_camera->transferring(QVector3D(-m_NormalTransferSpeed, 0, 0));
        break;
    case Qt::Key::Key_D:
        m_camera->transferring(QVector3D(m_NormalTransferSpeed, 0, 0));
        break;

    case Qt::Key::Key_E:
        m_camera->rotation(m_NormalRotateSpeed);
        break;
    case Qt::Key::Key_Q:
        m_camera->rotation(-m_NormalRotateSpeed);
        break;



    case Qt::Key::Key_V:
        m_currentObject->vertexScaling(10 * QVector3D(m_NormalScaleSpeed, m_NormalScaleSpeed, m_NormalScaleSpeed));
        break;
    case Qt::Key::Key_C:
        m_currentObject->vertexScaling(-10 * QVector3D(m_NormalScaleSpeed, m_NormalScaleSpeed, m_NormalScaleSpeed));
        break;

    case Qt::Key::Key_R:
        m_currentObject->reflection();
        break;

    case::Qt::Key::Key_T:
        m_currentObject->rotation(m_NormalRotateSpeed);
    }

    this->update();
}

void Viewport::mousePressEvent(QMouseEvent *event)
{
#ifdef DEBUG
    qDebug() << "Viewport::mousePressEvent ";
#endif

    if(m_ObjectsToDraw.empty())
        return;

    switch (event->buttons())
    {
    case Qt::LeftButton:
    {
        if(m_currentObject)
            m_currentObject->setColor(m_colorCurrentObject);

        m_oldMousePosition = event->localPos();

#ifdef DEBUG
    qDebug() << "\tLeftButton\n\t\tscreen" << m_oldMousePosition;
#endif

        m_oldMousePosition = m_camera->ScreenToWorld(m_oldMousePosition);

        QVector4D wordClick(m_oldMousePosition.x(), m_oldMousePosition.y(), 0, 1);
#ifdef DEBUG
    qDebug() << "\t\tworld" << wordClick;
#endif

        m_currentObject = this->findNearestObject(QVector3D(wordClick));

        if(!m_currentObject)
        {
            return;
        }

        m_colorCurrentObject = m_currentObject->getColor();
        m_currentObject->setColor(QColorConstants::Red);
        break;
    }
    }

    this->update();
}

void Viewport::mouseReleaseEvent(QMouseEvent *event)
{
#ifdef DEBUG
    qDebug() << "Viewport::mouseReleaseEvent " << event;
#endif

    this->update();
}

void Viewport::mouseMoveEvent(QMouseEvent *event)
{
#ifdef DEBUG
    qDebug() << "Viewport::mouseMoveEvent " << event;
#endif
    if(m_currentObject && (event->buttons() & Qt::LeftButton))
    {
        QPointF newPosition = m_camera->ScreenToWorld(event->localPos());
        QPointF differentBetweenPosition = m_oldMousePosition - newPosition;
        m_currentObject->shift(QVector3D(- differentBetweenPosition.x(), - differentBetweenPosition.y(), 0));

        m_oldMousePosition = newPosition;
    }

    this->update();
}

void Viewport::wheelEvent(QWheelEvent *event)
{
#ifdef DEBUG
    qDebug() << "Viewport::wheelEvent " << event << "\n\tmod: "<< event->modifiers();
#endif

    QPoint angel = event->angleDelta();
    if(m_currentObject && event->modifiers() == Qt::NoModifier)
    {
        m_currentObject->scale(QVector3D(m_wheelSpeed * angel.y(), m_wheelSpeed * angel.y(), 0));
    }
    else if(event->modifiers() == Qt::ControlModifier)
    {
        m_camera->scaling(QVector3D(m_wheelSpeed * angel.y(), m_wheelSpeed * angel.y(), 0));
    }

    this->update();
}

void Viewport::scaleCurrentObjectWithKeys(const Qt::Key &keyPress)
{
    if(!m_currentObject)
        return;

    switch (keyPress)
    {
    case Qt::Key::Key_Plus:
        this->m_currentObject->scale(QVector3D(m_NormalScaleSpeed, m_NormalScaleSpeed, 0));
        break;
    case Qt::Key::Key_Minus:

        this->m_currentObject->scale(QVector3D(- m_NormalScaleSpeed, - m_NormalScaleSpeed, 0));
        break;

    default:
        break;
    }

    this->update();
}

void Viewport::shiftCurrentObjectWithKeys(const Qt::Key &keyPress)
{
    if(!m_currentObject)
        return;

    switch(keyPress)
    {
    case Qt::Key::Key_Left:
        this->m_currentObject->shift(QVector3D(-m_NormalTransferSpeed, 0, 0));
        break;
    case Qt::Key::Key_Right:
        this->m_currentObject->shift(QVector3D(m_NormalTransferSpeed, 0, 0));
        break;
    case Qt::Key::Key_Up:
        this->m_currentObject->shift(QVector3D(0, m_NormalTransferSpeed, 0));
        break;
    case Qt::Key::Key_Down:
        this->m_currentObject->shift(QVector3D(0, -m_NormalTransferSpeed, 0));
        break;

    default:
        break;
    }

    this->update();
}
