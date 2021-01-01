#ifndef GAUSSSOLVER_H
#define GAUSSSOLVER_H

#include<QVector>



class GaussSolver
{
public:
    GaussSolver(const QVector<QVector<qreal>> &a_matrix,
                const QVector<qreal> &a_f);
    GaussSolver();

    bool Solve(QVector<qreal> &answer);
    void updateSystem(const QVector<QVector<qreal>> &a_matrix,
                      const QVector<qreal> &a_f);
private:
    bool straightRun();
    bool reverseRun();

    QVector<QVector<qreal>> m_matrix;
    QVector<qreal> m_f;

    friend std::ostream &operator<< (std::ostream &out, const GaussSolver &gaussSolver);
};

#endif // GAUSSSOLVER_H
