#include "universaldifferentialsweepmethod.h"
#include "rungekuttamethodforsystems.h"

#include <QDebug>
#define DEBUG

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
        )
{
    std::function<QVector<qreal>(const qreal&, const QVector<qreal>&)> F
            = [&](const qreal& t, const QVector<qreal>& x) -> QVector<qreal>
    {
        return {p(t) * x[0] + x[1],
                q(t) * x[0],
                f(t) * x[0]};
    };

    QVector<QPair<qreal, QVector<qreal>>> uvw
            = rungeKuttaMethodForSystem(F,QPair<qreal, QVector<qreal>>(begin,
                                                                       {a.first,
                                                                       -b.first,
                                                                        g.first}),
                                        begin,end,countOfSteps);
    QVector<QPair<qreal, QVector<qreal>>> abg
            = rungeKuttaMethodForSystem(F,QPair<qreal, QVector<qreal>>(end,
                                                                       {a.second,
                                                                       -b.second,
                                                                        g.second}),
                                        begin,end,countOfSteps);

    std::reverse(abg.begin(), abg.end());

    int size = abg.size();

    QVector<QPair<qreal, QVector2D>> result(size);

    qreal zn;

    for(int i = 0; i < size; ++i)
    {
        zn = abg[i].second[0] * uvw[i].second[1]
                - abg[i].second[1] * uvw[i].second[0];

        if(!zn)
        {
            throw QString("division by zero");
        }

        result[i].first = abg[i].first;

        result[i].second[0] = -(abg[i].second[0] * uvw[i].second[2]
                - abg[i].second[2] * uvw[i].second[0]) / zn;
        result[i].second[1] = -(abg[i].second[1] * uvw[i].second[2]
                - abg[i].second[2] * uvw[i].second[1]) / zn;
    }

    return result;
}
