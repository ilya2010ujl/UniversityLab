#ifndef UNIVERSALDIFFERENTIALSWEEPMETHOD_H
#define UNIVERSALDIFFERENTIALSWEEPMETHOD_H

#include <QVector2D>

QVector<QPair<qreal, QVector2D>> universalDifferentialSweepMethod(
            const std::function<qreal(const qreal&)>&p,
            const std::function<qreal(const qreal&)>&q,
            const std::function<qreal(const qreal&)>&f,
            const qreal& begin,
            const qreal& end,
            const QPair<qreal, qreal>& a,
            const QPair<qreal, qreal>& b,
            const QPair<qreal, qreal>& g,
            const QPair<qreal, qreal>& functionConditions,
            const QPair<qreal, qreal>& derivativeConditions,
            const int &countOfSteps);

#endif // UNIVERSALDIFFERENTIALSWEEPMETHOD_H
