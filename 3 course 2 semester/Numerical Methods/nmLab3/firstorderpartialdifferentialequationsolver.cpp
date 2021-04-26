#include "firstorderpartialdifferentialequationsolver.h"

#define DEBUG

#ifdef DEBUG
    #include <QDebug>
#endif

QVector<QVector<qreal>> firstOrderPartialDifferentialEquationSolver(
        const std::function<qreal(const qreal& x, const qreal& t)> &f,
        const qreal &c,
        const qreal &a,
        const qreal &b,
        const std::function<qreal(const qreal &x)> &phi,
        const std::function<qreal(const qreal &t)> &csi,
        const qreal &T,
        const int& countHorizontalSteps,
        const int& countVertiacalSteps)
{
    QVector<QVector<qreal>> result(countHorizontalSteps + 1);

    for(int i = 0; i <= countHorizontalSteps; ++i)
    {
        result[i].resize(countVertiacalSteps + 1);
    }

    qreal h = (b - a) / countHorizontalSteps;
    qreal tay = T / countVertiacalSteps;
    qreal x, t;

    for(int i = 0; i <= countHorizontalSteps; ++i)
    {
        x = a + h * i;
        result[i][0] = phi(x);
    }

    for(int i = 0; i <= countVertiacalSteps; ++i)
    {
        t = tay * i;
        result[0][i] = csi(t);
    }

    for(int n = 1; n <= countHorizontalSteps; ++n)
    {
        x = a + n * h;
        for(int j = 1; j <= countVertiacalSteps; ++j)
        {
            t = tay * j;
            result[n][j] = result[n-1][j]
                    + h * f(x - h, t) / c
                    + h * (result[n-1][j-1] - result[n-1][j])/(tay * c);
        }
    }

    return result;
}
