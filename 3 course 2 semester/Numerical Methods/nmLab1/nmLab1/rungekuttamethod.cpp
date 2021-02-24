#include "rungekuttamethod.h"

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
