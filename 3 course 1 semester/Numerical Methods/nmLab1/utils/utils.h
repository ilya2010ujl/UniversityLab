#ifndef UTILS_H
#define UTILS_H

#include <QVector>
#include "Eigen/Dense"
#include <limits>

void generateRandomVectorsForSystem(QVector<double> &a,
                                    QVector<double> &b,
                                    QVector<double> &c,
                                    QVector<double> &f,
                                    unsigned int &WhenP,
                                    QVector<double> &p,
                                    unsigned int &WhenQ,
                                    QVector<double> &q,
                                    QVector<double> &x,
                                    const unsigned int &size = rand(),
                                    const int &maxInVectors = std::numeric_limits<int>::max());

void generateRandomVectorsForSystemWhereXIdentity(QVector<double> &a,
                                    QVector<double> &b,
                                    QVector<double> &c,
                                    QVector<double> &f,
                                    unsigned int &WhenP,
                                    QVector<double> &p,
                                    unsigned int &WhenQ,
                                    QVector<double> &q,
                                    QVector<double> &x,
                                    const unsigned int &size = rand(),
                                    const int &maxInVectors = std::numeric_limits<int>::max());

void fillMatrix(Eigen::MatrixXd &Matrix,
                 const QVector<double> &a,
                 const QVector<double> &b,
                 const QVector<double> &c,
                 const unsigned int &WhenP,
                 const QVector<double> &p,
                 const unsigned int &WhenQ,
                 const QVector<double> &q);

void qVectorFromEigenVector(QVector<double> &Qvector, const Eigen::VectorXd &Evector);

double estimationOfSolutionAccuracy(const QVector<double> &x, const QVector<double> &xSolve);

double relativeSolutionError(const QVector<double> &x, const QVector<double> &xSolve, const double &q = 1);

#endif // UTILS_H
