#include "rungekuttamethod.h"

#include <QDebug>
#define DEBUG

QVector<qreal> solveK(const std::function<qreal (const QVector2D &)> &f,
                      const QVector2D &initialPoint,
                      const qreal &h)
{
    // К[0], K[1], К[2] для 3го порядка (110),
    // К[0], K[1], K[3], K[4] - для 4го порядка(111)
    QVector<qreal> K(5);

    K[0] = h * f(initialPoint);
    K[1] = h * f(initialPoint + QVector2D(h/3, K[0]/3));
    K[2] = h * f(initialPoint + QVector2D(2 * h /3, 2 * K[1] / 3));
    K[3] = h * f(initialPoint + QVector2D(2 * h / 3, - K[0] / 3 + K[1]));
    K[4] = h * f(initialPoint + QVector2D(h , K[0] - K[1] + K[3]));

    return K;
}

QVector<QVector2D> rungeKuttaMethodDoublingHalvingStep(const std::function<qreal (const QVector2D &)> &f,
                                                       const QVector2D &initialCondition,
                                                       const qreal &begin,
                                                       const qreal &end,
                                                       const qreal &maxLocalError,
                                                       const qreal &minStep)
{
#ifdef DEBUG
    int errorReached = 0, errorNotReached = 0;
#endif

    qreal h = qAbs(begin - end) / 10;

    qreal distanseToEnd, distanseToEndWithStep, LocalError, endIntegration;

    QVector<QVector2D> result(1);

    int direction;

    if(begin == initialCondition.x())
    {
        direction = 1;
        endIntegration = end;
    }
    else
    {
        direction = -1;
        endIntegration = begin;
    }

    QVector<qreal> K;

    result[0] = initialCondition;

    int i = 1;

    while(true)
    {
        while(direction * (result[i - 1].x() + direction * h) > direction * endIntegration)
        {
            h /= 2.;
        }

        distanseToEndWithStep = qAbs(endIntegration - (result[i - 1].x() + direction * h));

        if(distanseToEndWithStep < minStep)
        {
            distanseToEnd = qAbs(end - result[i - 1].x());
            if(distanseToEnd >= 2 * minStep)
            {
                result.push_back(QVector2D(endIntegration - direction * minStep, 0));
                result.push_back(QVector2D(endIntegration, 0));

                K = solveK(f, result[i - 1], result[i].x() - result[i - 1].x());

                result[i].setY(result[i - 1].y() + (K[0] + 3 * K[2]) / 4);
#ifdef DEBUG
    LocalError = qAbs((K[0] + 3 * K[1] + 3 * K[3] + K[4]) / 8
            - (K[0] + 3 * K[2]) / 4);

    if(LocalError > maxLocalError)
    {
        ++errorNotReached;
    }
    else
    {
        ++errorReached;
    }

    qDebug() << result[i] << LocalError;
#endif
                K = solveK(f, result[i], direction * minStep);

                result[i + 1].setY(result[i].y() + (K[0] + 3 * K[2]) / 4);
#ifdef DEBUG
    LocalError = qAbs((K[0] + 3 * K[1] + 3 * K[3] + K[4]) / 8
            - (K[0] + 3 * K[2]) / 4);

    if(LocalError > maxLocalError)
    {
        ++errorNotReached;
    }
    else
    {
        ++errorReached;
    }

    qDebug() << result[i + 1] << LocalError;
#endif
            }
            else if(distanseToEnd <= 1.5 * minStep)
            {
                result.push_back(QVector2D(endIntegration, 0));

                K = solveK(f, result[i - 1], (endIntegration - result[i - 1].x()));

                result[i].setY(result[i - 1].y() + (K[0] + 3 * K[2]) / 4);

#ifdef DEBUG
    LocalError = qAbs((K[0] + 3 * K[1] + 3 * K[3] + K[4]) / 8
            - (K[0] + 3 * K[2]) / 4);

    if(LocalError > maxLocalError)
    {
        ++errorNotReached;
    }
    else
    {
        ++errorReached;
    }

    qDebug() << result[i - 1] << LocalError;
#endif
            }
            else
            {
                result.push_back(QVector2D(result[i - 1].x() + (endIntegration - result[i - 1].x())/2, 0));
                result.push_back(QVector2D(endIntegration, 0));

                K = solveK(f, result[i - 1], result[i].x() - result[i - 1].x());

                result[i].setY(result[i - 1].y() + (K[0] + 3 * K[2]) / 4);
#ifdef DEBUG
    LocalError = qAbs((K[0] + 3 * K[1] + 3 * K[3] + K[4]) / 8
            - (K[0] + 3 * K[2]) / 4);

    if(LocalError > maxLocalError)
    {
        ++errorNotReached;
    }
    else
    {
        ++errorReached;
    }

    qDebug() << result[i] << LocalError;
#endif
                K = solveK(f, result[i], result[i + 1].x() - result[i].x());

                result[i + 1].setY(result[i].y() + (K[0] + 3 * K[2]) / 4);
#ifdef DEBUG
    LocalError = qAbs((K[0] + 3 * K[1] + 3 * K[3] + K[4]) / 8
            - (K[0] + 3 * K[2]) / 4);

    if(LocalError > maxLocalError)
    {
        ++errorNotReached;
    }
    else
    {
        ++errorReached;
    }

    qDebug() << result[i + 1] << LocalError;
#endif
            }
            break;
        }
        else
        {
            while(true)
            {
                if(h < minStep)
                {
                    h = minStep;
                    K = solveK(f, result[i - 1], direction * h);
                    result.push_back(QVector2D(result[i - 1].x() + direction * h, result[i - 1].y() + (K[0] + 3 * K[2]) / 4));
                    break;
                }

                K = solveK(f, result[i - 1], direction * h);

                LocalError = qAbs((K[0] + 3 * K[1] + 3 * K[3] + K[4]) / 8
                        - (K[0] + 3 * K[2]) / 4);

                if(LocalError > maxLocalError)
                {
                    h /= 2.;
                }
                else
                {
                    result.push_back(QVector2D(result[i - 1].x() + direction * h, result[i - 1].y() + (K[0] + 3 * K[2]) / 4));

                    if(LocalError < maxLocalError / 8)
                    {
                        h *= 2.;
                    }

                    break;
                }
            };
        }
#ifdef DEBUG
    if(LocalError > maxLocalError)
    {
        ++errorNotReached;
    }
    else
    {
        ++errorReached;
    }

    qDebug() << result[i - 1] << LocalError;
#endif
        ++i;
    }

#ifdef DEBUG
    qDebug() << "errorReached: " << errorReached;
    qDebug() << "errorNotReached: " << errorNotReached;
#endif

    return result;
}
