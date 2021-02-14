#include <QCoreApplication>

// метод парабол
bool parabolaMethod(const std::function<qreal(const qreal&)> &f,
                     const quint64& numberOfIteration,
                     const qreal& delta,
                     const qreal& a_u1,
                     const qreal& a_u2,
                     const qreal& a_u3,
                     qreal &result)
{
    qreal u1 = a_u1, u2 = a_u2, u3 = a_u3,
            Ju1, Ju2, Ju3, Jw,
            delta_minus, delta_plus,
            w;

    Ju1 = f(u1);
    Ju2 = f(u2);
    Ju3 = f(u3);
    delta_minus = Ju1 - Ju2;
    delta_plus = Ju3 - Ju2;

    int i = 0;

    while(!(delta_minus >= 0 && delta_plus >= 0 &&
           delta_plus + delta_minus > 0))
    {
        u2 = u1 + i * delta;
        ++i;
        Ju2 = f(u2);
        delta_minus = Ju1 - Ju2;
        delta_plus = Ju3 - Ju2;

        if(u2 > u3)
        {
            return false;
        }
    }

    for(quint64 i = 0; i < numberOfIteration; ++i)
    {
        Ju1 = f(u1);
        Ju2 = f(u2);
        Ju3 = f(u3);
        delta_minus = Ju1 - Ju2;
        delta_plus = Ju3 - Ju2;
        w = u2 + ((u3 - u2) * (u3 - u2) * delta_minus -
                  (u2 - u1) * (u2 - u1) * delta_plus) /
        (2 * ((u3 - u2) * delta_minus + (u2 - u1) * delta_plus));
        Jw = f(w);

        if(w < u2)
        {
            if(Jw < Ju2)
            {
                u3 = u2;
                u2 = w;
            }
            else if(Jw > Ju2)
            {
                u1 = w;
            }
            else
            {
                if(Ju1 > Ju2)
                {
                    u3 = u2;
                    u2 = w;
                }
                else if(Ju2 > Ju3)
                {
                    u1 = w;
                }
            }
        }
        else if(w > u2)
        {
            if(Jw < Ju2)
            {
                u1 = u2;
                u2 = w;
            }
            else if(Jw > Ju2)
            {
                u3 = w;
            }
            else
            {
                if(Ju3 > Ju2)
                {
                    u1 = u2;
                    u2 = w;
                }
                else if(Ju1 > Ju2)
                {
                    u3 = w;
                }
            }
        }
        else
        {
            // TODO
            Ju1 = f(u1);
            Ju2 = f(u2);
            Ju3 = f(u3);
            delta_minus = Ju1 - Ju2;
            delta_plus = Ju3 - Ju2;

            int i = 0;

            while(!(delta_minus >= 0 && delta_plus >= 0 &&
                   delta_plus + delta_minus > 0))
            {
                u2 = u1 + i * delta;
                ++i;
                Ju2 = f(u2);
                delta_minus = Ju1 - Ju2;
                delta_plus = Ju3 - Ju2;

                if(u2 > u3)
                {
                    result = u2;
                }
            }
        }
    }

    return true;
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

    qreal result;

    parabolaMethod(f, 100, 0.01, -1.5, -1, 1, result);

    qDebug() << result << f(result);

    return 0;
}
