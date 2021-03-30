#ifndef RUNGEKUTTAMETHODFORSYSTEMS_H
#define RUNGEKUTTAMETHODFORSYSTEMS_H

#include <QVector>
#include <QVector2D>
#include <functional>
#include <QPair>

QVector<qreal> product(const qreal& number, const QVector<qreal>& vector);
QVector<qreal> product(const QVector<qreal>& vector, const qreal& number);

QVector<qreal> sum(const QVector<qreal>& left, const QVector<qreal>& right);

QVector<QVector<qreal>> solveK(const std::function<
                                    QVector<qreal>(const qreal&, const QVector<qreal>&)
                               > &f,
                      const QPair<
                                    qreal, QVector<qreal>
                               >& initialPoint,
                      const qreal &h);

QVector<QPair<qreal, QVector<qreal>>> rungeKuttaMethodForSystem(const std::function<
                                                            QVector<qreal>(const qreal&, const QVector<qreal>&)
                                                       > &f,
                                                       const QPair<
                                                            qreal, QVector<qreal>
                                                       > &initialCondition,
                                                       const qreal &begin,
                                                       const qreal &end,
                                                       const int &countOfSteps);


#endif // RUNGEKUTTAMETHODFORSYSTEMS_H
