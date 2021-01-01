#ifndef UTILS_H
#define UTILS_H

#include <QtGlobal>
#include <QVector3D>

QT_BEGIN_NAMESPACE
namespace utils
{
    qreal distanceFromPointToLine(const QVector3D &point, const QVector3D &beginLine, const QVector3D &endLine);
    qreal distanceFromPointToLineSegment(const QVector3D &point, const QVector3D &beginLine, const QVector3D &endLine);
}
QT_END_NAMESPACE

#endif // UTILS_H
