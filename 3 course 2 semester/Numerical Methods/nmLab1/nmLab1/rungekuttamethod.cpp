#include "rungekuttamethod.h"

QVector3D solveK(const std::function<qreal (const QVector2D &)> &f,
                 const QVector2D &x, const qreal &h)
{
    QVector3D result;

    result.setX(h * f(x));
    result.setY(h * f(x + QVector2D(h/2, result.x()/2)));
    result.setZ(h * f(x + QVector2D(h, -result.x() + 2 * result.y())));

    return result;
}

QVector<QVector2D> RungeKuttaMethod(const std::function<qreal (const QVector2D &)> &f,
                                    const QVector2D &initialCondition,
                                    const qreal &begin,
                                    const qreal &end,
                                    const qreal& epsilon)
{
    QVector<QVector2D> result(1);
    result[0] = initialCondition;

    QVector3D K;

    qreal h = (end - begin) / 10;

    int i = 1;

    while(true)
    {
        result.push_back(QVector2D());

        if(end - (result[i - 1].x() + h) < epsilon)
        {
            if(end - result[i - 1].x() >= 2 * epsilon)
            {
                result.push_back(QVector2D());

                result[i].setX(end - epsilon);
                result[i + 1].setX(end);

                K = solveK(f, result[i - 1], h);
                result[i].setY(result[i - 1].y() + (K.x() + 4 * K.y() + K.z()) / 6);

                K = solveK(f, result[i], h);
                result[i + 1].setY(result[i].y() + (K.x() + 4 * K.y() + K.z()) / 6);
            }
            else if(end - result[i - 1].x() <= 1.5 * epsilon)
            {
                result[i].setX(end);

                K = solveK(f, result[i - 1], h);
                result[i].setY(result[i - 1].y() + (K.x() + 4 * K.y() + K.z()) / 6);
            }
            else if(1.5 * epsilon < end - result[i - 1].x() &&
                    end - result[i - 1].x() < 2 * epsilon)
            {
                result.push_back(QVector2D());

                result[i].setX(end - (end - result[i-1].x()) / 2);
                result[i + 1].setX(end);

                K = solveK(f, result[i - 1], h);
                result[i].setY(result[i - 1].y() + (K.x() + 4 * K.y() + K.z()) / 6);

                K = solveK(f, result[i], h);
                result[i + 1].setY(result[i].y() + (K.x() + 4 * K.y() + K.z()) / 6);
            }
            break;
        }
        else
        {
            result[i].setX(result[i - 1].x() + h);
        }

        K = solveK(f, result[i - 1], h);

        result[i].setY(result[i - 1].y() + (K.x() + 4 * K.y() + K.z()) / 6);

        h /= 2;

        if(h < epsilon)
        {
            h = epsilon;
        }
        ++i;
    }

    return result;
}
