#include <QCoreApplication>

#include <QVector>

qreal HammingDistance(const QVector<qreal> &left, const QVector<qreal> &right)
{
    qint32 size = left.size();

    qreal dist = 0;

    for(qint32 i = 0; i < size; ++i)
    {
        dist += qAbs(left[i] - right[i]);
    }

    return dist / size;
}

QVector<QVector<qreal>> dissimilariryMatrix(const QVector<QVector<qreal>>& objectEvaluation)
{
    qint32 size = objectEvaluation.size();

    QVector<QVector<qreal>> dMatrix(size, QVector<qreal>(size));

    for(qint32 i = 0; i < size; ++i)
    {
        for(qint32 j = 0; j < size; ++j)
        {
            dMatrix[i][j] = HammingDistance(objectEvaluation[i],
                                            objectEvaluation[j]);
        }
    }

    return dMatrix;
}

template<class T>
void printMatrix(const QVector<QVector<T>>& matrix)
{
    qint32 size = matrix.size();

    for(qint32 i = 0; i < size; ++i)
    {
        qDebug() << matrix[i];
    }
}

QVector<QVector<qreal>> similarityMatrix(const QVector<QVector<qreal>>& dissimilariryMatrix)
{
    qint32 size = dissimilariryMatrix.size();

    QVector<QVector<qreal>> sMatrix(size, QVector<qreal>(size));

    for(qint32 i = 0; i < size; ++i)
    {
        for(qint32 j = 0; j < size; ++j)
        {
            sMatrix[i][j] = 1 - dissimilariryMatrix[i][j];
        }
    }

    return sMatrix;
}

QVector<QVector<qreal>> Union(const QVector<QVector<qreal>>& left,
                              const QVector<QVector<qreal>>& right)
{
    qint32 size = left.size();

    QVector<QVector<qreal>> Union(size, QVector<qreal>(size));

    for(qint32 i = 0; i < size; ++i)
    {
        for(qint32 j = 0; j < size; ++j)
        {
            Union[i][j] = qMax(left[i][j], right[i][j]);
        }
    }

    return Union;
}

QVector<QVector<qreal>> maxTcomposition(const QVector<QVector<qreal>>& left,
                                        const QVector<QVector<qreal>>& right,
                                        const std::function<qreal(const qreal&, const qreal&)> &T =
        [](const qreal& left, const qreal& right) -> qreal
{
    return qMin(left, right);
})
{
    qint32 size = left.size();

    QVector<QVector<qreal>> mTcomposition(size, QVector<qreal>(size));

    QVector<qreal> tmp(size);

    for(qint32 i = 0; i < size; ++i)
    {
        for(qint32 j = 0; j < size; ++j)
        {
            for(qint32 k = 0; k < size; ++k)
            {
                tmp[k] = T(left[i][k], right[k][j]);
            }
            mTcomposition[i][j] = *std::max_element(tmp.begin(), tmp.end());
        }
    }

    return mTcomposition;
}

bool isEqual(const QVector<QVector<qreal>>& left,
             const QVector<QVector<qreal>>& right)
{
    qint32 size = left.size();

    for(qint32 i = 0; i < size; ++i)
    {
        for(qint32 j = 0; j < size; ++j)
        {
            if(left[i][j] != right[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

QVector<QVector<qreal>> transitiveClosure(const QVector<QVector<qreal>>& matrix,
                                          const std::function<qreal(const qreal&, const qreal&)> &T =
          [](const qreal& left, const qreal& right) ->qreal
  {
      return qMin(left, right);
  })
{
    QVector<QVector<qreal>> uMatrix = matrix, degreeMatrix = maxTcomposition(matrix, matrix, T), prevDegreeMatrix = matrix;

    qint32 size = matrix.size();

    qint32 countOfIteration = 0;

    while(!isEqual(degreeMatrix, prevDegreeMatrix) && size)
    {
        uMatrix = Union(uMatrix, degreeMatrix);
        prevDegreeMatrix = degreeMatrix;
        degreeMatrix = maxTcomposition(matrix, degreeMatrix, T);

        ++countOfIteration;
        --size;
    }

    qDebug() << "max degree: " << countOfIteration + 1;

    return uMatrix;
}

QVector<qreal> uniqueValues(const QVector<QVector<qreal>>& matrix)
{
    qint32 size = matrix.size();

    QVector<qreal> uValues;

    for(qint32 i = 0; i < size; ++i)
    {
        for(qint32 j = 0; j < size; ++j)
        {
            if(uValues.indexOf(matrix[i][j]) == -1)
            {
                uValues.push_back(matrix[i][j]);
            }
        }
    }

    std::sort(uValues.begin(), uValues.end());

    return uValues;
}

QVector<QVector<qint32>> unitIfGreaterOrEqual(const QVector<QVector<qreal>>& matrix,
                                     const qreal &value)
{
    qint32 size = matrix.size();

    QVector<QVector<qint32>> res(size, QVector<qint32>(size, 0));

    for(qint32 i = 0; i < size; ++i)
    {
        for(qint32 j = 0; j < size; ++j)
        {
            if(matrix[i][j] >= value)
            {
                res[i][j] = 1;
            }
        }
    }

    return res;
}

void decompositionTheorem(const QVector<QVector<qreal>>& matrix)
{
    QVector<qreal> uValues = uniqueValues(matrix);

    qint32 countValues = uValues.size();

    for(qint32 i = 0; i < countValues; ++i)
    {
        qDebug() << uValues[i];
        printMatrix(unitIfGreaterOrEqual(matrix, uValues[i]));
        qDebug() << '\n';
    }
}

bool checktransitiveClosure(const QVector<QVector<qreal>> &transitiveClosure,
                            const std::function<qreal(const qreal&, const qreal&)> &T =
[](const qreal& left, const qreal& right) -> qreal
{
return qMin(left, right);
})
{
    qint32 size = transitiveClosure.size();

    QVector<QVector<qreal>> tc2 = maxTcomposition(transitiveClosure, transitiveClosure, T);

    for(qint32 i = 0; i < size; ++i)
    {
        for(qint32 j = 0; j < size; ++j)
        {
            if(tc2[i][j] > transitiveClosure[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    QVector<QVector<qreal>> dMatrix = dissimilariryMatrix(
                {
                    {0.8, 0.7, 0.7,0.3,0},
                    {0.5,   1, 0.5,  0,0},
                    {0.5, 0.6, 0.8,0.4,0.2},
                    {0.9, 0.5, 0.3,0.2,0.2},
                    {0.6, 0.8, 0.9,0.3,0.1},
                    {0.2, 0.4, 0.6,0.8,0.9}
                });

    qDebug() << "dissimilariryMatrix: ";
    printMatrix(dMatrix);
    qDebug() << '\n';

    QVector<QVector<qreal>> sMatrix = similarityMatrix(dMatrix);

    qDebug() << "dissimilariryMatrix: ";
    printMatrix(sMatrix);
    qDebug() << '\n';

    std::function<qreal(const qreal&, const qreal&)> T = [&](const qreal&left, const qreal&right) -> qreal
    {
        qreal x = left, y = right;
        qreal b=-0.5;
        return qMax(0., (-2+2*b+(x+y)*(2-2*b)+x*y*(2*b-1))/(1+b+(x+y)*(-b)+x*y*b));
    };

    QVector<QVector<qreal>> tMatrix = transitiveClosure(sMatrix, T);
    qDebug() << "transitiveClosure: ";
    printMatrix(tMatrix);
    qDebug() << "checktransitiveClosure: " << checktransitiveClosure(tMatrix, T);
    qDebug() << '\n';

    decompositionTheorem(tMatrix);

    return 0;
}
