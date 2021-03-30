#include "rungekuttamethodforsystems.h"

#include <QDebug>
// #define DEBUG

QVector<qreal> product(const QVector<qreal> &vector, const qreal &number)
{
    int size = vector.size();

    QVector<qreal> result(size);

    for(int i = 0; i < size; ++i)
    {
        result[i] = vector[i] * number;
    }

    return result;
}

QVector<qreal> product(const qreal& number, const QVector<qreal>& vector)
{
    return product(vector, number);
}

QVector<qreal> sum(const QVector<qreal> &left, const QVector<qreal> &right)
{
    int size = left.size();

    QVector<qreal> result(size);

    for(int i = 0; i < size; ++i)
    {
        result[i] = left[i] + right[i];
    }

    return result;
}

QVector<QVector<qreal>> solveK(const std::function<
                                    QVector<qreal>(const qreal&, const QVector<qreal>&)
                               > &f,
                      const QPair<
                                    qreal, QVector<qreal>
                               >& initialPoint,
                      const qreal &h)
{
    QVector<QVector<qreal>> K(4);

    K[0] = product(h, f(initialPoint.first,
                        initialPoint.second));
    K[1] = product(h, f(initialPoint.first + h/2,
                        sum(
                            initialPoint.second,
                            product(K[0], 0.5)
                            )
                        ));
    K[2] = product(h, f(initialPoint.first + h/2,
                        sum(
                            initialPoint.second,
                            product(K[1], 0.5)
                            )
                        ));
    K[3] = product(h, f(initialPoint.first + h,
                        sum(
                            initialPoint.second,
                            K[2]
                            )
                        ));

    return K;
}

QVector<QPair<qreal, QVector<qreal>>> rungeKuttaMethodForSystem(const std::function<
                                                            QVector<qreal>(const qreal&, const QVector<qreal>&)
                                                       > &f,
                                                       const QPair<
                                                            qreal, QVector<qreal>
                                                       > &initialCondition,
                                                       const qreal &begin,
                                                       const qreal &end,
                                                       const int &countOfSteps)
{
    qreal h = qAbs(end - begin) / countOfSteps;

    int direction;
    qreal beginIntegration = initialCondition.first;

    QVector<QPair<qreal, QVector<qreal>>> result(countOfSteps + 1);
    result[0] = initialCondition;

    QVector<QVector<qreal>> K;

    if(begin == initialCondition.first)
    {
        direction = 1;
    }
    else
    {
        direction = -1;
    }

    for(int i = 1; i <= countOfSteps; ++i)
    {
        K = solveK(f, result[i - 1], direction * h);

        result[i].first = beginIntegration + direction * h * i;
        result[i].second = sum(
                    result[i-1].second,
                product(1.0/6.0,
                        sum(
                            sum(
                                sum(K[0],K[3]),
                                product(2, K[1])
                                ),
                            product(2, K[2])
                            )));
    }

    return result;
}
