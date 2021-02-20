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

QVector<qreal> product(const QVector<QVector<qreal>> &matrix, const QVector<qreal> &vector)
{
    quint64 size = vector.size();

    QVector<qreal> result(size, 0);

    for(quint64 i = 0; i < size; ++i)
    {
        for(quint64 j = 0; j < size; ++j)
        {
            result[i] += matrix[i][j] * vector[i];
        }
    }

    return result;
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

// Метод Ньютона многомерной минимизации
void SteepestDescentMethod(std::function<qreal(const QVector<qreal>&)> &f,
                        std::function<QVector<qreal>(std::function<qreal(const QVector<qreal>&)>&, const QVector<qreal>&)> &grad,
                        std::function<qreal(const QVector<qreal>&)>& norm,
                        std::function<QVector<QVector<qreal>>(const std::function<qreal(const QVector<qreal>&)> &, const QVector<qreal>&)> &hessian,
                        std::function<QVector<QVector<qreal>>(const QVector<QVector<qreal>> &)> &inverseMatrix,
                        const QVector<qreal> &initialApproximation,
                        QVector<qreal> &result,
                        const qreal& epsilon,
                        const quint64& numberOfIteration)
{
    QVector<qreal> u0 = initialApproximation;
    QVector<qreal> g;

    std::function<qreal(const qreal&)> alphaFunction;

    for(quint64 i = 0; i < numberOfIteration; ++i)
    {
        g = grad(f, u0);

        if(norm(g) < epsilon)
        {
            break;
        }

        u0 = sum(u0, product(-1, product(inverseMatrix(hessian(f, u0)), g)));
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

    std::function<QVector<QVector<qreal>>(const std::function<qreal(const QVector<qreal>&)> &, const QVector<qreal>&)> hessian
            = [] (const std::function<qreal(const QVector<qreal>&)> &f , const QVector<qreal>&x) -> QVector<QVector<qreal>>
    {
        qreal epsilon = 0.001;

        quint64 size = x.size();

        QVector<qreal> first, second, third, fourth;

        QVector<QVector<qreal>> hessian(size);

        for(quint64 i = 0; i < size; ++i)
        {
            hessian[i].resize(size);
            for(quint64 j = 0; j < size; ++j)
            {
                first = second = third = fourth = x;

                first[i] += epsilon;
                first[j] += epsilon;

                second[i] += epsilon;
                second[j] -= epsilon;

                third[i] -= epsilon;
                third[j] += epsilon;

                fourth[i] -= epsilon;
                fourth[j] -= epsilon;

                second = product(-1, second);
                third = product(-1, third);

                hessian[i][j] = (f(first) - f(second) - f(third) + f(fourth))
                        / ( 4 * epsilon * epsilon);
            }
        }

        return hessian;
    };

    QVector<qreal> result;

    qDebug() << result << f(result);

    return 0;
}
