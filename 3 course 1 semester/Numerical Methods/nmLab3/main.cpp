#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include "utils/utils.h"
#include "findmineigenvalue.h"
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()

int main()
{
    // srand(static_cast<unsigned int>(time(0)));

    int ranges[] = {2, 50};
    int countOfIteration = 5;

    for(int rangeEigen: ranges)
    {
        for(qreal accuracy = 1e-5f; accuracy >= 1e-8f; accuracy*=1e-3f)
        {
            for(int dimension = 10; dimension <= 50; dimension+=20)
            {
                qreal sumEigenvalueAccuracy = 0;
                qreal sumEigenvectorAccuracy = 0;
                qreal sumR = 0;
                qreal sumIter = 0;
                for(int iteration = 0; iteration < countOfIteration; ++iteration)
                {
                    QVector<QVector<qreal>> matrix;
                    QVector<QVector<qreal>> eigenVectors;
                    QVector<qreal> eigenValues;

                    GenerateMatrixWithEigenValues(matrix, eigenValues, eigenVectors, dimension, rangeEigen);

                    int minIndex = indexMinAbsElement(eigenValues);
                    qreal minEigenvalue;
                    QVector<qreal> EigenVector;
                    QVector<qreal> initialApproximation(dimension, 1);
                    qreal r;
                    int realNumberOfIteration;

                    if(!FindMinEigenValue(matrix, minEigenvalue, EigenVector, accuracy, accuracy,
                                      initialApproximation, r, realNumberOfIteration))
                    {
                        --iteration;
                        continue;
                    }

                    sumEigenvalueAccuracy += qAbs(minEigenvalue - eigenValues[minIndex]);
                    sumEigenvectorAccuracy += estimationOfSolutionAccuracy(EigenVector, eigenVectors[minIndex]);
                    sumR += r;
                    sumIter += realNumberOfIteration;
                }
                qDebug() << "dimension: " << dimension;
                qDebug() << "rangeEigen: " << rangeEigen;
                qDebug() << "accuracy: " << accuracy;
                qDebug() << "sr EigenvalueAccuracy: " << sumEigenvalueAccuracy / countOfIteration;
                qDebug() << "sr EigenvectorAccuracy: " << sumEigenvectorAccuracy / countOfIteration;
                qDebug() << "sr R: " << sumR / countOfIteration;
                qDebug() << "sr Iter: " << sumIter / countOfIteration << '\n';
            }
        }
    }
}

