#ifndef RUNGEKUTTAMETHOD_H
#define RUNGEKUTTAMETHOD_H

#include <QVector>
#include <QVector2D>
#include <functional>

QVector3D SolveThirdOrderK(const std::function<qreal(const QVector2D&)> &f,
                 const QVector2D& x, const qreal& h);

QVector<QVector2D> ThirdOrderRungeKuttaMethod(const std::function<qreal (const QVector2D &)> &f,
                                    const QVector2D &initialCondition,
                                    const qreal &begin,
                                    const qreal &end,
                                    const qreal& epsilon);

QVector4D SolveFourthOrderK(const std::function<qreal(const QVector2D&)> &f,
                 const QVector2D& x, const qreal& h);

QVector<QVector2D> FourthOrderRungeKuttaMethod(const std::function<qreal (const QVector2D &)> &f,
                                    const QVector2D &initialCondition,
                                    const qreal &begin,
                                    const qreal &end,
                                    const qreal& epsilon);

#endif // RUNGEKUTTAMETHOD_H
