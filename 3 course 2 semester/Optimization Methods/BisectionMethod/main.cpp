#include <QCoreApplication>
#include <functional>

// метод деления отрезка пополам
qreal BisectionMethod(const std::function<qreal(const qreal&)> &f,
                     const qreal& begin, const qreal& end,
                     const quint64& numberOfIteration,
                     const qreal& epsilon,
                     const qreal& delta)
{
    qreal a = begin, b = end, u1, u2, Ju1, Ju2;

    for(quint64 i = 0; i < numberOfIteration; ++i)
    {
        u1 = (b + a - delta) / 2;
        u2 = (b + a + delta) / 2;

        Ju1 = f(u1);
        Ju2 = f(u2);

        if(Ju1 < Ju2)
        {
            b = u2;
        }
        else if(Ju1 > Ju2)
        {
            a = u1;
        }
        else
        {
            a = u1;
            b = u2;
        }

        if(b - a < epsilon)
        {
            return (b + a) / 2;
        }
    }

    return (b + a) / 2;
}

int main()
{
    qreal ai[] = {1,1,1,-3,1,1};
    std::function<qreal(const qreal&)> f = [&](const qreal &x) -> qreal
    {
        qreal pow = 1, sum = 0;

        for(int i = 0; i < 6; ++i)
        {
            sum += ai[i]  * pow;
            pow *= x;
        }

        return sum;
    };

    qreal result = BisectionMethod(f, -2, 1, 100, 0.01, 0.01);

    qDebug() << result << f(result);

    return 0;
}
