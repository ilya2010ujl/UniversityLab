#include "utils.h"
#include <QtGlobal>
#include <QtMath>

void GenerateMatrixWithEigenValues(QVector<QVector<qreal>> &matrix,
                                   QVector<qreal> &eigenValues,
                                   QVector<QVector<qreal>> &eigenVectors,
                                   const uint &matrixDimension,
                                   const qreal &maxEigenValues)
{
    Eigen::VectorXd EeigenValues(matrixDimension);
    randomEigenVector(EeigenValues, maxEigenValues);

    Eigen::MatrixXd EDiagonalMatrix(matrixDimension, matrixDimension);
    EDiagonalMatrix.setIdentity();
    fillMainDiagonal(EDiagonalMatrix, EeigenValues);

    Eigen::MatrixXd EIdentityMatrix(matrixDimension, matrixDimension);
    EIdentityMatrix.setIdentity();

    Eigen::VectorXd w(matrixDimension);
    randomEigenVector(w);
    w.normalize();

    Eigen::MatrixXd H = EIdentityMatrix - 2 * w * w.transpose();
    Eigen::MatrixXd HTranspose = H.transpose();

    EigenMatrixToQVectorQvector(H * EDiagonalMatrix * HTranspose, matrix);
    EigenMatrixToQVectorQvector(HTranspose, eigenVectors);
    EigenVectorToQVector(EeigenValues, eigenValues);
}

void randomEigenVector(Eigen::VectorXd &vector,
                       const double &maxElementInVector)
{
    for(uint i = 0; i < vector.size(); ++i)
    {
        vector[i] = static_cast<double>(rand())/ static_cast<double>(RAND_MAX) *
                (maxElementInVector + maxElementInVector) - maxElementInVector;
    }
}

void randomEigenVector(Eigen::VectorXd &vector)
{
    for(uint i = 0; i < vector.size(); ++i)
    {
        vector[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    }
}

void fillMainDiagonal(Eigen::MatrixXd &matrix,
                           const Eigen::VectorXd &diagonal)
{
    for(uint i = 0; i < diagonal.size(); ++i)
    {
        matrix(i, i) = diagonal(i);
    }
}

void EigenMatrixToQVectorQvector(const Eigen::MatrixXd &Ematrix,
                                 QVector<QVector<qreal>> &Qmatrix)
{
    uint row = Ematrix.rows();
    uint col = Ematrix.cols();

    Qmatrix.resize(row);

    for(uint i = 0; i < row; ++i)
    {
        Qmatrix[i].resize(col);
    }

    for(uint i = 0; i < row; ++i)
    {
        for(uint j = 0; j < col; ++j)
        {
            Qmatrix[i][j] = Ematrix(i, j);
        }
    }
}

void EigenVectorToQVector(const Eigen::VectorXd &Evector,
                          QVector<qreal> &Qvector)
{
    uint size = Evector.size();

    Qvector.resize(size);

    for(uint i = 0; i < size; ++i)
    {
        Qvector[i] = Evector[i];
    }
}

void QVectorQvectorToEigenMatrix(const QVector<QVector<qreal>> &Qmatrix,
                                 Eigen::MatrixXd &Ematrix)
{
    uint row = Qmatrix.size();
    uint col = Qmatrix[0].size();

    Ematrix.resize(row, col);

    for(uint i = 0; i < row; ++i)
    {
        for(uint j = 0; j < col; ++j)
        {
            Ematrix(i,j) = Qmatrix[i][j];
        }
    }
}

void QVectorToEigenVector(const QVector<qreal> &Qvector,
                          Eigen::VectorXd &Evector)
{
    int size = Qvector.size();

    Evector.resize(size);

    for(int i = 0; i < size; ++i)
    {
        Evector(i) = Qvector[i];
    }
}

int indexMinAbsElement(const QVector<qreal> &Qvector)
{
    int minIndex = 0;

    for(int i = 1; i < Qvector.size(); ++i)
    {
        if(qAbs(Qvector[i]) < qAbs(Qvector[minIndex]))
        {
            minIndex = i;
        }
    }

    return minIndex;
}

qreal angleBetweenVectors(Eigen::VectorXd evector1,
                          Eigen::VectorXd evector2)
{
    qreal cosA = 0;

    evector1.normalize();
    evector2.normalize();

    for(int i = 0; i < evector1.size(); ++i)
    {
        cosA += evector1[i] * evector2[i];
    }

    return qAcos(cosA);
}

qreal estimationOfSolutionAccuracy(const QVector<double> &x, const QVector<double> &xSolve)
{
    double EstimationOfSolutionAccuracy = -1;

    for(int i = 0; i < x.size(); ++i)
    {
        if(EstimationOfSolutionAccuracy < abs(xSolve[i] - x[i]))
        {
            EstimationOfSolutionAccuracy = abs(xSolve[i] - x[i]);
        }
    }

    return EstimationOfSolutionAccuracy;
}
