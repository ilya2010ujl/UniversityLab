#include <QCoreApplication>
#include <functional>
#include <QVector>

QVector<qreal> product(const qreal& number, const QVector<qreal> &vector)
{
    quint64 size = vector.size();
    QVector<qreal> result(size);

    for(quint64 i = 0; i < size; ++i)
    {
        result[i] = vector[i] * number;
    }

    return result;
}

QVector<qreal> product(const QVector<qreal> &vector, const qreal& number)
{
    return product(number, vector);
}

QVector<qreal> sum(const QVector<qreal> &left, const QVector<qreal> &right)
{
    quint64 size = left.size();

    QVector<qreal> result(size);

    for(quint64 i = 0; i < size; ++i)
    {
        result[i] = left[i] + right[i];
    }

    return result;
}

// Метод наискорейшего спуска
void SteepestDescentMethod(std::function<qreal(const QVector<qreal>&)> &f,
                        std::function<QVector<qreal>(std::function<qreal(const QVector<qreal>&)>&, const QVector<qreal>&)> &grad,
                        std::function<qreal(const QVector<qreal>&)>& norm,
                        std::function<qreal(const std::function<qreal(const qreal&)> &)> &optimization,
                        const QVector<qreal> &initialApproximation,
                        QVector<qreal> &result,
                        const qreal& epsilon,
                        const quint64& numberOfIteration)
{
    QVector<qreal> u0 = initialApproximation;
    qreal a;
    QVector<qreal> g;

    std::function<qreal(const qreal&)> alphaFunction;

    for(quint64 i = 0; i < numberOfIteration; ++i)
    {
        g = grad(f, u0);

        if(norm(g) < epsilon)
        {
            break;
        }

        alphaFunction = [&](const qreal& alpha) -> qreal
        {
            return f(sum(u0, product(-alpha, g)));
        };

        a = optimization(alphaFunction);

        u0 = sum(u0, product(-a, g));
    }

    result = u0;
}

int main()
{
    std::function<qreal(const QVector<qreal>&)> f = [](const QVector<qreal>& x) -> qreal
    {
        return x[0] * x[0] + x[0]* x[1] + x[1] * x[1] + 7;
    };

    std::function<QVector<qreal>(std::function<qreal(const QVector<qreal>&)>&, const QVector<qreal>&)> grad =
            [](std::function<qreal(const QVector<qreal>&)>& f, const QVector<qreal>&x) -> QVector<qreal>
            {
                qreal epsilon = 0.001;

                quint64 size = x.size();

                QVector<qreal> result(size), tmpLeft, tmpRight;

                for(quint64 i = 0; i < size; ++i)
                {
                    tmpLeft = x;
                    tmpRight = x;

                    tmpLeft[i] += epsilon;
                    tmpRight[i] -= epsilon;

                    result[i] = (f(tmpLeft) - f(tmpRight)) / (2 * epsilon);
                }

                return result;
            };

    std::function<qreal(const QVector<qreal>&)> norm = [](const QVector<qreal>& vector) -> qreal
    {
        qreal sum = 0;

        quint64 size = vector.size();

        for(quint64 i = 0; i < size; ++i)
        {
            sum += vector[i] * vector[i];
        }

        return qSqrt(sum);
    };

    std::function<qreal(const std::function<qreal(const qreal&)> &)> optimization =
    [](const std::function<qreal(const qreal&)> &f) -> qreal
    {
        qreal a = 0, b = 100, u1, u2, Ju1, Ju2,
                alpha = (qSqrt(5) - 1)/2, alpha1 = (3 - sqrt(5))/2;

        u1 = a + alpha1 * (b-a);
        u2 = a + alpha * (b-a);

        Ju1 = f(u1);
        Ju2 = f(u2);

        for(quint64 i = 0; i < 300; ++i)
        {
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

            if(b - a < 0.0001)
            {
                return (b + a) / 2;
            }
        }

        return (b + a) / 2;
        return 0;
    };

    QVector<qreal> result;

    SteepestDescentMethod(f, grad, norm, optimization, {10, 10}, result, 0.001, 100);

    qDebug() << result << f(result);

    return 0;
}
