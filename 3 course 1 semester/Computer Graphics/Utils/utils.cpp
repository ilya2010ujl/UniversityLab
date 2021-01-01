#include <QtMath>

#include "utils.h"

// проверить когда делене на 0
qreal utils::distanceFromPointToLine(const QVector3D &point, const QVector3D &beginLine, const QVector3D &endLine)
{
    QVector3D directionVector(endLine.x() - beginLine.x(),
                              endLine.y() - beginLine.y(),
                              endLine.z() - beginLine.z());

    QVector3D hypotenuse = point - beginLine;

    QVector3D crossProduct = QVector3D::crossProduct(directionVector, hypotenuse);

    return crossProduct.length() / directionVector.length();
}

qreal utils::distanceFromPointToLineSegment(const QVector3D &point,
                                            const QVector3D &beginLineSegment,
                                            const QVector3D &endLineSegment)
{
    qreal distanceFromPointToBeginLineSegment = (point - beginLineSegment).length();
    qreal distanceFromPointToEndLineSegment = (point - endLineSegment).length();

    QVector3D NearestPoint = distanceFromPointToEndLineSegment < distanceFromPointToBeginLineSegment ?
                endLineSegment : beginLineSegment;
    QVector3D NoNearestPoint = distanceFromPointToEndLineSegment > distanceFromPointToBeginLineSegment ?
                endLineSegment : beginLineSegment;

    qreal cosinus = QVector3D::dotProduct(NoNearestPoint - NearestPoint, point - NearestPoint);

    if(cosinus < 0)
    {
        return distanceFromPointToEndLineSegment < distanceFromPointToBeginLineSegment ?
                    distanceFromPointToEndLineSegment : distanceFromPointToBeginLineSegment;
    }
    else
    {
        return distanceFromPointToLine(point, beginLineSegment, endLineSegment);
    }
}
