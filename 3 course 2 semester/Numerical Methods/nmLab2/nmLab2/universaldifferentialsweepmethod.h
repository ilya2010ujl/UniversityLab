#ifndef UNIVERSALDIFFERENTIALSWEEPMETHOD_H
#define UNIVERSALDIFFERENTIALSWEEPMETHOD_H

#include <QVector2D>

QVector<QPair<qreal, QVector2D>> universalDifferentialSweepMethod(
        const std::function<qreal(const qreal&)> &p,
        const std::function<qreal(const qreal&)> &q,
        const std::function<qreal(const qreal&)> &f,
        const qreal& begin, // a
        const qreal &end, // b
        const QPair<qreal, qreal> &a, // a1 a2
        const QPair<qreal, qreal> &b, // b1 b2
        const QPair<qreal, qreal> &g, // g1 g2
        const int &countOfSteps
        );

#endif // UNIVERSALDIFFERENTIALSWEEPMETHOD_H
