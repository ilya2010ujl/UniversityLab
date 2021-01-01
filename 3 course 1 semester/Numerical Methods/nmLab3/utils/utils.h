#ifndef UTILS_H
#define UTILS_H

#include <QVector>
#include <limits>
#include "Eigen/Dense"

void GenerateMatrixWithEigenValues(QVector<QVector<qreal>> &matrix,
                                   QVector<qreal> &eigenValues,
                                   QVector<QVector<qreal>> &eigenVectors,
                                   const uint &matrixDimension,
                                   const qreal &maxEigenValues);

void randomEigenVector(Eigen::VectorXd &vector,
                       const double &maxElementInVector);

void randomEigenVector(Eigen::VectorXd &vector);

void fillMainDiagonal(Eigen::MatrixXd &matrix,
                      const Eigen::VectorXd &diagonal);

void EigenMatrixToQVectorQvector(const Eigen::MatrixXd &Ematrix,
                                 QVector<QVector<qreal>> &Qmatrix);

void EigenVectorToQVector(const Eigen::VectorXd &Evector,
                          QVector<qreal> &Qvector);

void QVectorQvectorToEigenMatrix(const QVector<QVector<qreal>> &Qmatrix,
                                 Eigen::MatrixXd &Ematrix);

void QVectorToEigenVector(const QVector<qreal> &Qvector,
                          Eigen::VectorXd &Evector);

int indexMinAbsElement(const QVector<qreal> &Qvector);

qreal angleBetweenVectors(Eigen::VectorXd evector1,
                          Eigen::VectorXd evector2);

qreal estimationOfSolutionAccuracy(const QVector<double> &x, const QVector<double> &xSolve);

#endif // UTILS_H
