#include <QCoreApplication>

#include "firstorderpartialdifferentialequationsolver.h"

int main()
{
    std::function<qreal(const qreal& x, const qreal& t)> f = [](const qreal& x, const qreal& t) -> qreal
    {
        Q_UNUSED(t)

        return t-x;
    };

    qreal a = 0;
    qreal b = 1;

    std::function<qreal(const qreal& x, const qreal& t)> u = [](const qreal& x, const qreal& t) -> qreal
    {
        return 5*t-x-qExp(x)/26.*(cos(t)-5*sin(t));
    };

    std::function<qreal(const qreal &x)> phi = [&](const qreal& x) -> qreal
    {
        return u(x,0);
    };
    std::function<qreal(const qreal &t)> csi = [&](const qreal& t) -> qreal
    {
        return u(a,t);
    };

    qreal T = 1;
    qreal c = 5;
    int countHorizontalSteps = 5;
    int countVertiacalSteps = 10;

    QVector<QVector<double>> r = firstOrderPartialDifferentialEquationSolver(f,c,a,b,phi,csi,T,
                                                                             countHorizontalSteps, countVertiacalSteps);
    qreal h = (b - a) / countHorizontalSteps;
    qreal tay = T / countVertiacalSteps;
    qreal x, t;

    qDebug() << "h: " << h;
    qDebug() << "r: " << tay;
    qDebug() << "c*r/h: " << c*tay/h << '\n';

    QVector<qreal> pogr, maxPogr;
    qreal absMax;

    for(int i = 0; i < r.size(); ++i)
    {
        pogr.clear();

        x = a + i * h;
        for(int j = 0; j < r[i].size(); ++j)
        {
            t = tay * j;
            qDebug() << "("<< x << ',' << t << ")" << r[i][j] << u(x, t) << u(x, t) - r[i][j];
            pogr.push_back(u(x, t) - r[i][j]);
        }

        absMax = -1;

        for(int k = 0; k < pogr.size(); ++k)
        {
            if(absMax < qAbs(pogr[k]))
            {
                absMax = qAbs(pogr[k]);
            }
        }
        maxPogr.push_back(absMax);
        qDebug() << absMax;
        qDebug() << '\n';
    }

    absMax = -1;

    for(int k = 0; k < maxPogr.size(); ++k)
    {
        if(absMax < qAbs(maxPogr[k]))
        {
            absMax = qAbs(maxPogr[k]);
        }
    }

    qDebug() << absMax;

    return 0;
}
