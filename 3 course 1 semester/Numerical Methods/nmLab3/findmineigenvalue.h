#ifndef FINDMINEIGENVALUE_H
#define FINDMINEIGENVALUE_H

#include <QVector>

bool FindMinEigenValue(const QVector<QVector<qreal>> &matrix,
                       qreal &minEigenvalue,
                       QVector<qreal> &EigenVector,
                       const qreal &EpsilonMinEigenvalue,
                       const qreal &EpsilonEigenVector,
                       const QVector<qreal> &initialApproximation,
                       qreal &r,
                       int &realNumberOfIteration,
                       const uint &numberOfIteration = 1000);

#endif // FINDMAXEIGENVALUE_H
