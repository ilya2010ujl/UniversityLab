#ifndef RUNGEKUTTAMETHOD_H
#define RUNGEKUTTAMETHOD_H

#include <QVector>
#include <QVector2D>
#include <functional>

QVector<qreal> solveK(const std::function<qreal(const QVector2D&)> &f,
                      const QVector2D& initialPoint,
                      const qreal &h);

QVector<QVector2D> rungeKuttaMethodDoublingHalvingStep(const std::function<qreal(const QVector2D&)> &f,
                                                       const QVector2D &initialCondition,
                                                       const qreal &begin,
                                                       const qreal &end,
                                                       const qreal &maxLocalError,
                                                       const qreal &minStep);

#endif // RUNGEKUTTAMETHOD_H
