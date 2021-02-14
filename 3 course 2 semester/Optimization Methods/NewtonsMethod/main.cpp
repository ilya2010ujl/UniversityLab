#include <QCoreApplication>
#include <functional>
#include <QDebug>

// метод Ньютона
qreal NewtonsMethod(const std::function<qreal(const qreal&)> &f,
                    const std::function<qreal(const std::function<qreal(const qreal&)>&, const qreal&, const qreal&)> firstDerivation,
                    const std::function<qreal(const std::function<qreal(const qreal&)>&, const qreal&, const qreal&)> secondDerivation,
                    const qreal& betta,
                    const qreal& initialApproximation,
                    const quint64& numberOfIteration,
                    const qreal& epsilon)
{
    qreal uk = initialApproximation, J_, J__;

    for(quint64 i = 0; i < numberOfIteration; ++i)
    {
        J_ = firstDerivation(f, uk, betta);

        if(qAbs(J_) < epsilon)
        {
            return uk;
        }

        J__ = secondDerivation(f, uk, betta);

        uk = uk - J_ / J__;
    }

    return uk;
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

    std::function<qreal(const std::function<qreal(const qreal&)>&, const qreal&, const qreal&)>
            firstDeriavation = [](const std::function<qreal(const qreal&)>& f, const qreal& x0, const qreal& betta) -> qreal
    {
        return (f(x0 + betta) - f(x0 - betta)) / (2 * betta);
    },
            secondDeriavation = [](const std::function<qreal(const qreal&)>& f, const qreal& x0, const qreal& betta) -> qreal
    {
        return (-f(x0 + 2 * betta) + 16 * f(x0 + betta) - 30 * f(x0) + 16 * f(x0 - betta) - f(x0 - 2 * betta)) / (12 * betta * betta);
    };

    qreal result = NewtonsMethod(f, firstDeriavation, secondDeriavation, 0.01, 0, 100, 0.01);

    qDebug() << result << f(result);

    return 0;
}
