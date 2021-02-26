#include <QCoreApplication>
#include <functional>

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

QVector<qreal> product(const QVector<QVector<qreal>> &matrix, const QVector<qreal>& vector)
{
    quint64 size = vector.size();
    QVector<qreal> result(size, 0);

    for(quint64 i = 0; i < size; ++i)
    {
        for(quint64 j = 0; j < size; ++j)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

QVector<qreal> product(const QVector<qreal>& vector, const QVector<QVector<qreal>> &matrix)
{
    quint64 size = vector.size();
    QVector<qreal> result(size, 0);

    for(quint64 i = 0; i < size; ++i)
    {
        for(quint64 j = 0; j < size; ++j)
        {
            result[i] += matrix[j][i] * vector[j];
        }
    }

    return result;
}

QVector<QVector<qreal>> createIdentityMatrix(const quint64 size)
{
    QVector<QVector<qreal>> result(size);

    for(quint64 i = 0; i < size; ++i)
    {
        result[i].resize(size);
        result[i].fill(0);

        result[i][i] = 1;
    }

    return result;
}

// МЕТОД БАРЬЕРНЫХ ФУНКЦИЙ
QVector<qreal> BarrierFunctionMethod(
        const std::function<qreal(const QVector<double>&)>& f,
        const QVector<std::function<qreal(const QVector<double>&)>>& g,
        const std::function
        <
        std::function<qreal(const QVector<double>&)>
                (QVector<std::function<qreal(const QVector<double>&)>>)
        >& G,
        const std::function<QVector<double>(std::function<qreal(const QVector<double>&)>,
                                            const QVector<double>)> &minimize,
        const QVector<qreal>& initialX,
        const qreal& initialR,
        const qreal& dividerR,
        const qreal& epsilon)
{
    qreal r = initialR;
    QVector<qreal> x = initialX;
    std::function<qreal(const QVector<double>&)> toMinimize;
    std::function<qreal(const QVector<double>&)> penalty = G(g);

    while(r > epsilon)
    {
        toMinimize = [&](const QVector<double>& x) -> qreal
        {
            return f(x) + r * penalty(x);
        };

        qDebug() << x << toMinimize(x) << f(x) << penalty(x) << r;

        x = minimize(toMinimize, x);

        r /= dividerR;
    }

    return x;
}

int main()
{
    std::function<qreal(const QVector<double>&)> f = [](const QVector<double>& x) -> qreal
    {
        return x[0] * x[0] + 6 * x[0] + x[1] * x[1] + 9 * x[1];
    };

    QVector<std::function<qreal(const QVector<double>&)>> g(2);
    g[0] = [](const QVector<double>& x) -> qreal
    {
        return x[0];
    };
    g[1] = [](const QVector<double>& x) -> qreal
    {
        return x[1];
    };

    const std::function
    <
    std::function<qreal(const QVector<double>&)>
            (QVector<std::function<qreal(const QVector<double>&)>>)
    > G = [](QVector<std::function<qreal(const QVector<double>&)>> g) -> std::function<qreal(const QVector<double>&)>
    {
        int size = g.size();
        return [=](const QVector<double>& x) -> qreal
        {
            qreal sum = 0;
            for(int i = 0; i < size; ++i)
            {
                sum += 1 / g[i](x);
            }
            return sum;
        };
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

    std::function<QVector<QVector<qreal>>
                         (std::function<qreal(const QVector<qreal>&)>&, const QVector<qreal>&)> hessian
            = [](std::function<qreal(const QVector<qreal>&)>& f, const QVector<qreal>& x) -> QVector<QVector<qreal>>
    {
        int size = x.size();
        QVector<QVector<qreal>> result(size);

        qreal epsilon = 0.01;

        QVector<qreal> first, second, third, fourth;

        for(int i = 0; i < size; ++i)
        {
            result[i].resize(size);
            for(int j = 0; j < size; ++j)
            {
                first = x;
                first[i] += epsilon;
                first[j] += epsilon;
                second = x;
                second[i] += epsilon;
                second[j] -= epsilon;
                third = x;
                third[i] -= epsilon;
                third[j] += epsilon;
                fourth = x;
                fourth[i] -= epsilon;
                fourth[j] -= epsilon;

                result[i][j] = (f(first) - f(second) - f(third) + f(fourth)) / (4 * epsilon * epsilon);
            }
        }

        return result;
    };

    std::function<QVector<QVector<qreal>>(QVector<QVector<qreal>>)> inverseMatrix
            = [](QVector<QVector<qreal>> matrix) -> QVector<QVector<qreal>>
    {
            int size = matrix.size();

            QVector<QVector<qreal>> InverseMatrix = createIdentityMatrix(size);

            qreal R;

            for (int i = 0; i < size; ++i)
            {
                R = 1 / matrix[i][i];
                matrix[i] = product(matrix[i], R);
                InverseMatrix[i] = product(InverseMatrix[i], R);

                for(int j = i + 1; j < size; ++j)
                {
                    InverseMatrix[j] = sum(product(-1 * matrix[j][i], InverseMatrix[i]), InverseMatrix[j]);
                    matrix[j] = sum(product(-1 * matrix[j][i], matrix[i]), matrix[j]);
                }
            }

            for (int i = size - 1; i >= 0; --i)
            {
                for(int j = i - 1; j >= 0; --j)
                {
                    InverseMatrix[j] = sum(product(-1 * matrix[j][i], InverseMatrix[i]), InverseMatrix[j]);
                    matrix[j] = sum(product(-1 * matrix[j][i], matrix[i]), matrix[j]);
                }
            }

            return InverseMatrix;
    };

    std::function<QVector<double>(std::function<qreal(const QVector<double>&)>,
                                  const QVector<double>)> gaussMinimize =
            [&](std::function<qreal(const QVector<double>&)>,
            const QVector<double> initialX) -> QVector<double>
    {
        QVector<qreal> u0 = initialX;
        QVector<qreal> g;

        std::function<qreal(const qreal&)> alphaFunction;

        for(quint64 i = 0; i < 100; ++i)
        {
            g = grad(f, u0);

            if(norm(g) < 0.001)
            {
                break;
            }

            u0 = sum(u0, product(-1, product(g, inverseMatrix(hessian(f, u0)))));
        }

        return u0;
    };

    QVector<qreal> result = BarrierFunctionMethod(f, g, G, gaussMinimize, {1, 0.5}, 100, 10, 0.00001);

    qDebug() << result << f(result);

    return 0;
}
