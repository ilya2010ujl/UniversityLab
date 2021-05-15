#include <QCoreApplication>

#include <QVector>
#include <QVector2D>
#include <functional>
#include <QMap>

#include <QDebug>
#include <iostream>

QVector<QVector<QVector2D>> intermediateResultOperationInMatrix(
        const QVector<QVector2D> &leftFuzzyNumber,
        const QVector<QVector2D> &rightFuzzyNumber,
        const std::function<qreal(const qreal& left, const qreal& right)> &operation
        )
{
    int leftNumberCountValues = leftFuzzyNumber.size();
    int rightNumberCountValues = rightFuzzyNumber.size();

    QVector<QVector<QVector2D>> result(leftNumberCountValues);

    for(int i = 0; i < leftNumberCountValues; ++i)
    {
        result[i].resize(rightNumberCountValues);
    }

    for(int i = 0; i < leftNumberCountValues; ++i)
    {
        for(int j = 0; j < rightNumberCountValues; ++j)
        {
            result[i][j] = QVector2D
                    (
                        operation(leftFuzzyNumber[i][0], rightFuzzyNumber[j][0]),
                        qMin(leftFuzzyNumber[i][1], rightFuzzyNumber[j][1])
                    );
        }
    }

    return result;
}

QVector<QVector2D> operationOnFuzzyNumbers(
        const QVector<QVector2D> &leftFuzzyNumber,
        const QVector<QVector2D> &rightFuzzyNumber,
        const std::function<qreal(const qreal& left, const qreal& right)> &operation
        )
{
    QVector<QVector2D> intermediateResultOperation;

    int leftNumberCountValues = leftFuzzyNumber.size();
    int rightNumberCountValues = rightFuzzyNumber.size();

    for(int i = 0; i < leftNumberCountValues; ++i)
    {
        for(int j = 0; j < rightNumberCountValues; ++j)
        {
            intermediateResultOperation.push_back
                    (
                        QVector2D
                        (
                            operation(leftFuzzyNumber[i][0], rightFuzzyNumber[j][0]),
                                  qMin(leftFuzzyNumber[i][1], rightFuzzyNumber[j][1])
                        )
                    );
        }
    }

    QVector<qreal> uniqueValues;

    for(int i = 0; i < intermediateResultOperation.size(); ++i)
    {
        if(uniqueValues.indexOf(intermediateResultOperation[i][0]) == -1)
        {
            uniqueValues.push_back(intermediateResultOperation[i][0]);
        }
    }

    std::sort(uniqueValues.begin(), uniqueValues.end());

    int countUniqueValues = uniqueValues.size();

    QVector<QVector2D> result(countUniqueValues);

    for(int i = 0; i < countUniqueValues; ++i)
    {
        result[i] = QVector2D(uniqueValues[i], -1);
    }

    for(int i = 0; i < intermediateResultOperation.size(); ++i)
    {
        if(result[uniqueValues.indexOf(intermediateResultOperation[i][0])][1]
                < intermediateResultOperation[i][1])
        {
            result[uniqueValues.indexOf(intermediateResultOperation[i][0])][1] = intermediateResultOperation[i][1];
        }
    }

    return result;
}

void Pro4isla()
{
    QVector<QVector2D> leftFuzzyNumber = {{3,0}, {4,0.1}, {5,0.3}, {6, 0.5}, {7,1}, {8, 0.8}, {9,0}};
    QVector<QVector2D> rightFuzzyNumber = {{5,0}, {6,0.3}, {7,0.5}, {8, 0.9}, {9,1}, {10, 0.5}, {11, 0}};

    QVector<QVector<QVector2D>> IROIM = intermediateResultOperationInMatrix(leftFuzzyNumber, rightFuzzyNumber,
    [](const qreal& left, const qreal& right)
    {
        return qMax(left,right);
    });

    int leftNumberCountValues = leftFuzzyNumber.size();
    int rightNumberCountValues = rightFuzzyNumber.size();

    for(int i = 0; i < leftNumberCountValues; ++i)
    {
        for(int j = 0; j < rightNumberCountValues; ++j)
        {
            std::cout << IROIM[i][j][0] << '/' << IROIM[i][j][1] << "    ";
        }
        std::cout << '\n';
    }

    QVector<QVector2D> OOFN = operationOnFuzzyNumbers(leftFuzzyNumber, rightFuzzyNumber,
    [](const qreal& left, const qreal& right)
    {
        return qMax(left,right);
    });

    std::cout << '\n';
    for(int i = 0; i < OOFN.size(); ++i)
    {
        std::cout << OOFN[i][0] << ' ' << OOFN[i][1] << '\n';
    }
}

///

qreal hemmingDistance(const QVector<qreal>& left,
                      const QVector<qreal>& right)
{
    qint32 size = left.size();

    qreal res = 0;

    for(qint32 i = 0; i < size; ++i)
    {
        res += qAbs(left[i] - right[i]);
    }

    return res / size;
}

QVector<QVector<qreal>> dissimilarityMatrix(const QVector<QVector<qreal>> &Aabcde)
{
    qint32 size = Aabcde.size();

    QVector<QVector<qreal>> res(size);

    for(qint32 i = 0; i < size; ++i)
    {
        res[i].resize(size);
        for(qint32 j = 0; j < size; ++j)
        {
            res[i][j] = hemmingDistance(Aabcde[i], Aabcde[j]);
        }
    }

    return res;
}

QVector<QVector<qreal>> milarityMatrix(const QVector<QVector<qreal>> &dissimilarityMatrix)
{
    qint32 size = dissimilarityMatrix.size();

    QVector<QVector<qreal>> res(size);

    for(qint32 i = 0; i < size; ++i)
    {
        res[i].resize(size);
        for(qint32 j = 0; j < size; ++j)
        {
            res[i][j] = 1 - dissimilarityMatrix[i][j];
        }
    }

    return res;
}

void printMatrix(const QVector<QVector<qreal>> &matrix)
{
    qint32 size = matrix.size();

    for(qint32 i = 0; i < size; ++i)
    {
        for(qint32 j = 0; j < size; ++j)
        {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<QVector<qreal>> Aabcde =
    {
        {0.8, 0.7, 0.7, 0.3, 0},
        {0.5, 1, 0.5, 0, 0},
        {0.5, 0.6, 0.8, 0.4, 0.2},
        {0.9, 0.5, 0.3, 0.2, 0.2},
        {0.6, 0.8, 0.9, 0.3, 0.1},
        {0.2, 0.4, 0.6, 0.8, 0.9}
    };

    printMatrix(dissimilarityMatrix(Aabcde));
    qDebug() << '\n';
    printMatrix(milarityMatrix(dissimilarityMatrix(Aabcde)));



    return a.exec();
}
