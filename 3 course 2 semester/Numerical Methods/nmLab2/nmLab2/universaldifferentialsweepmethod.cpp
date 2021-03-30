#include "universaldifferentialsweepmethod.h"

#include "rungekuttamethodforsystems.h"

#include <QDebug>
#define DEBUG

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
            const int &countOfSteps)
{
    std::function<
            QVector<qreal>(const qreal&, const QVector<qreal>&)
                 > F = [&](const qreal&x, const QVector<qreal>&y) -> QVector<qreal>
    {
        Q_UNUSED(x);
        return {p(x) * y[0] + y[1], q(x) * y[0], f(x) * y[0]};
    };

    QVector<QPair<qreal, QVector<qreal>>> uvw =
            rungeKuttaMethodForSystem(F, QPair<qreal,
                                      QVector<qreal>>(begin,
                                      {a.first,-b.first,g.first}),
                                      begin, end, countOfSteps);

    QVector<QPair<qreal, QVector<qreal>>> abg =
            rungeKuttaMethodForSystem(F, QPair<qreal,
                                      QVector<qreal>>(end,
                                      {a.second,-b.second,g.second}),
                                      begin, end, countOfSteps);

    std::reverse(abg.begin(), abg.end());

    int size = uvw.size();

#ifdef DEBUG
    for(int i = 0; i < size; ++i)
    {
        qDebug() << uvw[i] << " | " << abg[i];
    }
#endif

    QVector<QPair<qreal, QVector2D>> result(size);

    qreal zn;

    for(int i = 0; i < size; ++i)
    {
        zn = abg[i].second[0] * uvw[i].second[1]
                - abg[i].second[1] * uvw[i].second[0];

        result[i].first = abg[i].first;

        result[i].second[0] = (abg[i].second[0] * uvw[i].second[2]
                - abg[i].second[2] * uvw[i].second[0])/zn;

        result[i].second[1] = (abg[i].second[1] * uvw[i].second[2]
                - abg[i].second[2] * uvw[i].second[1])/zn;
    }

    return result;
}
