#include "utils.h"
#include <cmath>
#include "stdlib.h"

void generateRandomVectorsForSystem(QVector<double> &a,
                                    QVector<double> &b,
                                    QVector<double> &c,
                                    QVector<double> &f,
                                    unsigned int &WhenP,
                                    QVector<double> &p,
                                    unsigned int &WhenQ,
                                    QVector<double> &q,
                                    QVector<double> &x,
                                    const unsigned int &size,
                                    const int &maxInVectors)
{
    Q_ASSERT(size >= 5);

    a.resize(size);
    b.resize(size);
    c.resize(size);
    f.resize(size);
    p.resize(size);
    q.resize(size);
    x.resize(size);

    Eigen::VectorXd X(size);

    WhenP = 1 + rand() % (size - 4);
    WhenQ = WhenP + 2;

    for (unsigned int i = 0; i < size ; ++i)
    {
        a[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxInVectors + maxInVectors) - maxInVectors;
        b[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxInVectors + maxInVectors) - maxInVectors;
        c[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxInVectors + maxInVectors) - maxInVectors;
        p[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxInVectors + maxInVectors) - maxInVectors;
        q[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxInVectors + maxInVectors) - maxInVectors;
        X[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxInVectors + maxInVectors) - maxInVectors;
    }
    c[0] = 0;
    b[0] = 0;

    p[WhenP] = a[WhenP];
    q[WhenQ] = a[WhenQ];
    p[WhenP + 1] = b[WhenP + 1];
    q[WhenQ + 1] = b[WhenQ + 1];
    p[WhenP - 1] = c[WhenP];
    q[WhenQ - 1] = c[WhenQ];

    qVectorFromEigenVector(x, X);

    Eigen::MatrixXd Matrix(size, size);
    fillMatrix(Matrix, a, b, c, WhenP, p, WhenQ, q);

    Eigen::VectorXd F(size);

    F = Matrix * X;

    qVectorFromEigenVector(f, F);
}

void generateRandomVectorsForSystemWhereXIdentity(QVector<double> &a,
                                                  QVector<double> &b,
                                                  QVector<double> &c,
                                                  QVector<double> &f,
                                                  unsigned int &WhenP,
                                                  QVector<double> &p,
                                                  unsigned int &WhenQ,
                                                  QVector<double> &q,
                                                  QVector<double> &x,
                                                  const unsigned int &size,
                                                  const int &maxInVectors)
{
    Q_ASSERT(size >= 5);

    a.resize(size);
    b.resize(size);
    c.resize(size);
    f.resize(size);
    p.resize(size);
    q.resize(size);

    x.resize(size);
    x.fill(1);

    WhenP = 1 + rand() % (size - 4);
    WhenQ = WhenP + 2;

    for (unsigned int i = 0; i < size ; ++i)
    {
        a[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxInVectors + maxInVectors) - maxInVectors;
        b[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxInVectors + maxInVectors) - maxInVectors;
        c[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxInVectors + maxInVectors) - maxInVectors;
        p[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxInVectors + maxInVectors) - maxInVectors;
        q[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxInVectors + maxInVectors) - maxInVectors;
    }
    c[0] = 0;
    b[0] = 0;

    p[WhenP] = a[WhenP];
    q[WhenQ] = a[WhenQ];
    p[WhenP + 1] = b[WhenP + 1];
    q[WhenQ + 1] = b[WhenQ + 1];
    p[WhenP - 1] = c[WhenP];
    q[WhenQ - 1] = c[WhenQ];

    Eigen::MatrixXd Matrix(size, size);
    fillMatrix(Matrix, a, b, c, WhenP, p, WhenQ, q);

    Eigen::VectorXd F(size);
    Eigen::VectorXd X(size);
    X.fill(1);
    F = Matrix * X;

    qVectorFromEigenVector(f, F);
}

void fillMatrix(Eigen::MatrixXd &Matrix,
                const QVector<double> &a,
                const QVector<double> &b,
                const QVector<double> &c,
                const unsigned int &WhenP,
                const QVector<double> &p,
                const unsigned int &WhenQ,
                const QVector<double> &q)
{
    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < a.size(); ++j)
        {
            if(static_cast<unsigned int>(i) == WhenP)
            {
                Matrix(i,j) = p[j];
            }
            else if(static_cast<unsigned int>(i) == WhenQ)
            {
                Matrix(i,j) = q[j];
            }
            else if(i == j)
            {
                Matrix(i,j) = a[i];
            }
            else if(i - j == -1)
            {
                Matrix(i,j) = b[i + 1];
            }
            else if(i - j == 1)
            {
                Matrix(i,j) = c[i];
            }
            else
            {
                Matrix(i,j) = 0;
            }
        }
    }
}

void qVectorFromEigenVector(QVector<double> &Qvector, const Eigen::VectorXd &Evector)
{
    for(int i = 0; i < Qvector.size(); ++i)
    {
        Qvector[i] = Evector[i];
    }
}

double estimationOfSolutionAccuracy(const QVector<double> &x, const QVector<double> &xSolve)
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

double relativeSolutionError(const QVector<double> &x, const QVector<double> &xSolve, const double &q)
{
    double relativeSolutionError = -1;

    for(int i = 0; i < x.size(); ++i)
    {
        if(abs(x[i]) > q)
        {
            if(relativeSolutionError < abs((x[i] - xSolve[i]) / x[i]))
            {
                relativeSolutionError = abs((x[i] - xSolve[i]) / x[i]);
            }
        }
        else
        {
            if(relativeSolutionError < abs(x[i] - xSolve[i]))
            {
                relativeSolutionError = abs(x[i] - xSolve[i]);
            }
        }
    }

    return relativeSolutionError;
}
