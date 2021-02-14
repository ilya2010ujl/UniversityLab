#include <QCoreApplication>
#include <functional>
#include <QtMath>
#include <QDebug>

// метод золотого сечения
qreal GoldenSectionSearch(const std::function<qreal(const qreal&)> &f,
                          const qreal& begin, const qreal& end,
                          const quint64& numberOfIteration,
                          const qreal& epsilon)
{
    qreal a = begin, b = end, u1, u2, Ju1, Ju2,
            alpha = (qSqrt(5) - 1)/2, alpha1 = (3 - sqrt(5))/2;

    u1 = a + alpha1 * (b-a);
    u2 = a + alpha * (b-a);

    for(quint64 i = 0; i < numberOfIteration; ++i)
    {

        Ju1 = f(u1);
        Ju2 = f(u2);

        if(Ju1 < Ju2)
        {
            b = u2;
            u2 = u1;
            Ju2 = Ju1;
            u1 = a + alpha1 * (b-a);
            Ju1 = f(u1);
        }
        else if(Ju1 > Ju2)
        {
            a = u1;
            u1 = u2;
            Ju1 = Ju2;
            u2 = a + alpha * (b-a);
            Ju2 = f(u2);
        }
        else
        {
            a = u1;
            b = u2;
            u1 = a + alpha1 * (b-a);
            u2 = a + alpha * (b-a);
            Ju1 = f(u1);
            Ju2 = f(u2);
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

    qreal result = GoldenSectionSearch(f, -2, 1, 100, 0.0001);

    qDebug() << result << f(result);

    return 0;
}
