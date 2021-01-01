#include "findmineigenvalue.h"

#include "Eigen/Dense"
#include "utils/utils.h"
#include "GaussSolver/gausssolver.h"
#include <QDebug>
#include <iostream>

// #define DEBUG

bool FindMinEigenValue(const QVector<QVector<qreal>> &matrix,
                       qreal &minEigenvalue,
                       QVector<qreal> &EigenVector,
                       const qreal &EpsilonMinEigenvalue,
                       const qreal &EpsilonEigenVector,
                       const QVector<qreal> &initialApproximation,
                       qreal &r,
                       int &realNumberOfIteration,
                       const uint &numberOfIteration)
{
    realNumberOfIteration = 0;

    Eigen::VectorXd ex;
    Eigen::VectorXd exPrev;
    QVectorToEigenVector(initialApproximation, ex);

    Eigen::VectorXd ev;
    Eigen::VectorXd evPrev;

    QVector<qreal> qx;
    QVector<qreal> qv;

    GaussSolver S;

    ev = ex;    // v[k]
    ev.normalize();
    EigenVectorToQVector(ev, qv);
    S.updateSystem(matrix, qv);
    if(!S.Solve(qx))
        return false;
    QVectorToEigenVector(qx, ex); // x[k + 1]
    ++realNumberOfIteration;

    for(uint i = 1; i < numberOfIteration; ++i)
    {
        evPrev = ev;    //  v[k - 1]
        exPrev = ex;    //  x[k]

        ev = ex;        // v[k]
        ev.normalize();

        EigenVectorToQVector(ev, qv);

        S.updateSystem(matrix, qv);

        if(!S.Solve(qx))    // x[k + 1]
            return false;

        QVectorToEigenVector(qx, ex);

        ++realNumberOfIteration;

        if( ((angleBetweenVectors(ex, exPrev) < EpsilonEigenVector) || (angleBetweenVectors(ex, -exPrev) < EpsilonEigenVector)) &&
                (qAbs(static_cast<double>(ev.transpose() * ex) -
                                static_cast<double>(evPrev.transpose() * exPrev)) < EpsilonMinEigenvalue) )
        {
#ifdef DEBUG
            qDebug() << "break angleBetweenVectors" << angleBetweenVectors(ex, exPrev);
#endif
            break;
        }
    }

    minEigenvalue = ev.transpose() * ex;
    minEigenvalue = 1 / minEigenvalue;

    EigenVectorToQVector(ev, EigenVector);

    Eigen::MatrixXd Ematrix;
    QVectorQvectorToEigenMatrix(matrix, Ematrix);

    r = (Ematrix * ev - minEigenvalue * ev).norm();

    return true;
}
