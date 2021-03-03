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

// метод дробления шага
void stepCrushingMethod(std::function<qreal(const QVector<qreal>&)> &f,
                        std::function<QVector<qreal>(std::function<qreal(const QVector<qreal>&)>&, const QVector<qreal>&)> &grad,
                        std::function<qreal(const QVector<qreal>&)>& norm,
                        const QVector<qreal> &initialApproximation,
                        QVector<qreal> &result,
                        const qreal& alpha,
                        const qreal& epsilon,
                        const quint64& numberOfIteration)
{
    QVector<qreal> u0 = initialApproximation, u1;
    qreal Ju0 = f(u0), Ju1, a = alpha;
    QVector<qreal> g = grad(f, u0);

    // qDebug() << "stepCrushingMethod begin" << "f" << f(u0) << u0 << "grad " << g;

    for(quint64 i = 0; i < numberOfIteration; ++i)
    {
        if(norm(g) < epsilon)
        {
            break;
        }

        u1 = sum(u0, product(-a,g));

        Ju1 = f(u1);

        if(Ju1 < Ju0)
        {
            u0 = u1;
            Ju0 = Ju1;
            g = grad(f, u0);
        }

        // qDebug() << "stepCrushingMethod" << "f" << f(u0) << u0 << "grad " << g;

        a /= 2;
    }

    result = u0;
}

int main()
{
    std::function<qreal(const QVector<qreal>&)> f = [](const QVector<qreal>& x) -> qreal
    {
        return x[0] * x[0] + 6 * x[0] + x[1] * x[1] + 9 * x[1];
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

    QVector<qreal> result = {1, 0.5};

    // stepCrushingMethod(f, grad, norm, {1, -1}, result, 2, 0.00001, 10000);

    qreal r = 1;
    qreal e = 0.0001;

    std::function<qreal(const QVector<qreal>&)> penalty = [](const QVector<qreal>& x) -> qreal
    {
        return 1/x[0] + 1/x[1];
    };


    // метод штрафных функций
    while(r > e)
    {
        std::function<qreal(const QVector<qreal>&)> toMinimize = [&](const QVector<qreal>& x) -> qreal
        {
            return f(x) + r * penalty(x);
        };

        // qDebug() << "toMinimize: " << toMinimize(result) << result;

        stepCrushingMethod(toMinimize, grad, norm, result, result, 0.05, 0.00001, 10);

        // qDebug() << "toMinimize adter minimize: " << toMinimize(result) << result;

        r /= 10;
    }

    qDebug() << result << f(result);

    return 0;
}
