#include "rungekuttamethod.h"

#include <QDebug>
#define DEBUG

QVector3D SolveThirdOrderK(const std::function<qreal (const QVector2D &)> &f,
                 const QVector2D &x, const qreal &h)
{
    QVector3D result;

    result.setX(h * f(x));
    result.setY(h * f(x + QVector2D(h/2, result.x()/2)));
    result.setZ(h * f(x + QVector2D(h, -result.x() + 2 * result.y())));

    return result;
}

QVector<QVector2D> ThirdOrderRungeKuttaMethod(const std::function<qreal (const QVector2D &)> &f,
                                    const QVector2D &initialCondition,
                                    const qreal &begin,
                                    const qreal &end,
                                    const qreal& epsilon)
{
    QVector<QVector2D> result(1);
    result[0] = initialCondition;

    QVector3D K;

    int direction = initialCondition.x() == begin ? 1 : - 1;

    qreal h = (end - begin) / 10;

    int i = 1;

    while(true)
    {
        result.push_back(QVector2D());

        if(qAbs((direction == 1 ? end : begin) - (result[i - 1].x() + direction * h)) < epsilon)
        {
            if(qAbs((direction == 1 ? end : begin) - result[i - 1].x()) >= 2 * epsilon)
            {
                result.push_back(QVector2D());

                result[i].setX((direction == 1 ? end : begin) - direction * epsilon);
                result[i + 1].setX(direction == 1 ? end : begin);

                K = SolveThirdOrderK(f, result[i - 1], direction * h);
                result[i].setY(result[i - 1].y() + (K.x() + 4 * K.y() + K.z()) / 6);

                K = SolveThirdOrderK(f, result[i], direction * h);
                result[i + 1].setY(result[i].y() + (K.x() + 4 * K.y() + K.z()) / 6);
            }
            else if(qAbs((direction == 1 ? end : begin) - result[i - 1].x()) <= 1.5 * epsilon)
            {
                result[i].setX(direction == 1 ? end : begin);

                K = SolveThirdOrderK(f, result[i - 1], direction * h);
                result[i].setY(result[i - 1].y() + (K.x() + 4 * K.y() + K.z()) / 6);
            }
            else if(1.5 * epsilon < qAbs((direction == 1 ? end : begin) - result[i - 1].x()) &&
                    qAbs((direction == 1 ? end : begin) - result[i - 1].x()) < 2 * epsilon)
            {
                result.push_back(QVector2D());

                result[i].setX((direction == 1 ? end : begin) - ((direction == 1 ? end : begin) - result[i-1].x()) / 2);
                result[i + 1].setX(direction == 1 ? end : begin);

                K = SolveThirdOrderK(f, result[i - 1], direction * h);
                result[i].setY(result[i - 1].y() + (K.x() + 4 * K.y() + K.z()) / 6);

                K = SolveThirdOrderK(f, result[i], direction * h);
                result[i + 1].setY(result[i].y() + (K.x() + 4 * K.y() + K.z()) / 6);
            }
            break;
        }
        else
        {
            result[i].setX(result[i - 1].x() + direction * h);
        }

        K = SolveThirdOrderK(f, result[i - 1], direction * h);

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

QVector4D SolveFourthOrderK(const std::function<qreal (const QVector2D &)> &f, const QVector2D &x, const qreal &h)
{
    QVector4D result;

    result.setX(h * f(x));
    result.setY(h * f(x + QVector2D(h/2, result.x()/2)));
    result.setZ(h * f(x + QVector2D(h/2, result.y()/2)));
    result.setW(h * f(x + QVector2D(h, result.z())));

    return result;
}

QVector<QVector2D> FourthOrderRungeKuttaMethod(const std::function<qreal (const QVector2D &)> &f,
                                               const QVector2D &initialCondition,
                                               const qreal &begin, const qreal &end, const qreal &epsilon)
{
    QVector<QVector2D> result(1);
    result[0] = initialCondition;

    QVector4D K;

    int direction = initialCondition.x() == begin ? 1 : - 1;

    qreal h = (end - begin) / 10;

    int i = 1;

    while(true)
    {
        result.push_back(QVector2D());

        if(qAbs((direction == 1 ? end : begin) - (result[i - 1].x() + direction * h)) < epsilon)
        {
            if(qAbs((direction == 1 ? end : begin) - result[i - 1].x()) >= 2 * epsilon)
            {
                result.push_back(QVector2D());

                result[i].setX((direction == 1 ? end : begin) - direction * epsilon);
                result[i + 1].setX(direction == 1 ? end : begin);

                K = SolveFourthOrderK(f, result[i - 1], direction * h);
                result[i].setY(result[i - 1].y() + (K.x() + 2 * K.y() + 2 * K.z() + K.w()) / 6);

                K = SolveFourthOrderK(f, result[i], direction * h);
                result[i + 1].setY(result[i].y() + (K.x() + 2 * K.y() + 2 * K.z() + K.w()) / 6);
            }
            else if(qAbs((direction == 1 ? end : begin) - result[i - 1].x()) <= 1.5 * epsilon)
            {
                result[i].setX(direction == 1 ? end : begin);

                K = SolveFourthOrderK(f, result[i - 1], direction * h);
                result[i].setY(result[i - 1].y() + (K.x() + 2 * K.y() + 2 * K.z() + K.w()) / 6);
            }
            else if(1.5 * epsilon < qAbs((direction == 1 ? end : begin) - result[i - 1].x()) &&
                    qAbs((direction == 1 ? end : begin) - result[i - 1].x()) < 2 * epsilon)
            {
                result.push_back(QVector2D());

                result[i].setX((direction == 1 ? end : begin) - ((direction == 1 ? end : begin) - result[i-1].x()) / 2);
                result[i + 1].setX(direction == 1 ? end : begin);

                K = SolveFourthOrderK(f, result[i - 1], direction * h);
                result[i].setY(result[i - 1].y() + (K.x() + 2 * K.y() + 2 * K.z() + K.w()) / 6);

                K = SolveFourthOrderK(f, result[i], direction * h);
                result[i + 1].setY(result[i].y() + (K.x() + 2 * K.y() + 2 * K.z() + K.w()) / 6);
            }
            break;
        }
        else
        {
            result[i].setX(result[i - 1].x() + direction * h);
        }

        K = SolveFourthOrderK(f, result[i - 1], direction * h);

        result[i].setY(result[i - 1].y() + (K.x() + 2 * K.y() + 2 * K.z() + K.w()) / 6);

        h /= 2;

        if(h < epsilon)
        {
            h = epsilon;
        }
        ++i;
    }

    return result;
}


QVector<QVector2D> methodRungeKuttaWithDoublingAndHalvingStep3rdAnd4thOrder(const std::function<qreal (const QVector2D &)> &f,
                                                                            const QVector2D &initialCondition,
                                                                            const qreal &begin,
                                                                            const qreal &end,
                                                                            const qreal &epsilon,
                                                                            const qreal &minStep)
{
    QVector<QVector2D> result(1);
    result[0] = initialCondition;

    QVector3D K3;
    QVector4D K4;

    int direction = initialCondition.x() == begin ? 1 : - 1;

    qreal h = (end - begin) / 10, en;

    int i = 1;

    while(true)
    {
        result.push_back(QVector2D());

        if(qAbs((direction == 1 ? end : begin) - (result[i - 1].x() + direction * h)) < minStep)
        {
            if(qAbs((direction == 1 ? end : begin) - result[i - 1].x()) >= 2 * minStep)
            {
                result.push_back(QVector2D());

                result[i].setX((direction == 1 ? end : begin) - direction * minStep);
                result[i + 1].setX(direction == 1 ? end : begin);

                K3 = SolveThirdOrderK(f, result[i - 1], direction * h);
                result[i].setY(result[i - 1].y() + (K3.x() + 4 * K3.y() + K3.z()) / 6);

                K3 = SolveThirdOrderK(f, result[i], direction * h);
                result[i + 1].setY(result[i].y() + (K3.x() + 4 * K3.y() + K3.z()) / 6);
            }
            else if(qAbs((direction == 1 ? end : begin) - result[i - 1].x()) <= 1.5 * minStep)
            {
                result[i].setX(direction == 1 ? end : begin);

                K3 = SolveThirdOrderK(f, result[i - 1], direction * h);
                result[i].setY(result[i - 1].y() + (K3.x() + 4 * K3.y() + K3.z()) / 6);
            }
            else if(1.5 * minStep < qAbs((direction == 1 ? end : begin) - result[i - 1].x()) &&
                    qAbs((direction == 1 ? end : begin) - result[i - 1].x()) < 2 * minStep)
            {
                result.push_back(QVector2D());

                result[i].setX((direction == 1 ? end : begin) - ((direction == 1 ? end : begin) - result[i-1].x()) / 2);
                result[i + 1].setX(direction == 1 ? end : begin);

                K3 = SolveThirdOrderK(f, result[i - 1], direction * h);
                result[i].setY(result[i - 1].y() + (K3.x() + 4 * K3.y() + K3.z()) / 6);

                K3 = SolveThirdOrderK(f, result[i], direction * h);
                result[i + 1].setY(result[i].y() + (K3.x() + 4 * K3.y() + K3.z()) / 6);
            }
            break;
        }
        else
        {

            while(true)
            {
                result[i].setX(result[i - 1].x() + direction * h);

                K3 = SolveThirdOrderK(f, result[i - 1], direction * h);
                K4 = SolveFourthOrderK(f, result[i - 1], direction * h);

                en = qAbs((K4.x() + 2 * K4.y() + 2 * K4.z() + K4.w()) - (K3.x() + 4 * K3.y() + K3.z())) / 6;

                if(en > epsilon)
                {
                    h /= 2;

                    if(h < minStep)
                    {
                        h = minStep;
                        break;
                    }
                }
                else
                {
                    if(en < epsilon / 8)
                    {
                        h *= 2;
                    }

                    if(h < minStep)
                    {
                        h = minStep;
                    }

                    while(result[i].x() + direction * h > (direction == 1 ? end : begin))
                    {
                        h /= 2;
                    }
                    break;
                }
            }

            result[i].setY(result[i - 1].y() + (K3.x() + 4 * K3.y() + K3.z()) / 6);
        }
        ++i;
    }

    return result;
}
