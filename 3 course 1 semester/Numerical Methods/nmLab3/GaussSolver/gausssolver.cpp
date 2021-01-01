#include "gausssolver.h"
#include <QDebug>

// #define DEBUG

GaussSolver::GaussSolver() {}

GaussSolver::GaussSolver(const QVector<QVector<qreal> > &a_matrix, const QVector<qreal> &a_f)
    : m_matrix(a_matrix), m_f(a_f)
{
    Q_ASSERT(m_f.size() == m_matrix.size());

    for(int i = 0; i < m_matrix.size(); ++i)
    {
        Q_ASSERT(m_matrix.size() == m_matrix[i].size());
    }
}

bool GaussSolver::Solve(QVector<qreal> &answer)
{
    if(!straightRun())
        return false;
    if(!reverseRun())
        return false;

    answer = m_f;

    return true;
}

void GaussSolver::updateSystem(const QVector<QVector<qreal> > &a_matrix,
                               const QVector<qreal> &a_f)
{
    m_matrix = a_matrix;
    m_f = a_f;
}

bool GaussSolver::straightRun()
{
    int size = m_f.size();

    for(int i = 0; i < size; ++i)
    {
        if(m_matrix[i][i] == 0)
            return false;

        qreal R = 1 / m_matrix[i][i];
        m_matrix[i][i] = 1;

        for(int j = i + 1; j < size; ++j)
        {
            m_matrix[i][j] *= R;
        }
        m_f[i] *= R;

#ifdef DEBUG
    qDebug() << "del" << m_matrix << m_f;
#endif

        for(int k = i + 1; k < size; ++k)
        {
            qreal R = m_matrix[k][i];
            m_matrix[k][i] = 0;

            for(int j = i + 1; j < size; ++j)
            {
                m_matrix[k][j] -= R * m_matrix[i][j];
            }

            m_f[k] -= R * m_f[i];
        }

#ifdef DEBUG
    qDebug() << "minus" << m_matrix << m_f;
#endif
    }

    return true;
}

bool GaussSolver::reverseRun()
{
    int size = m_f.size();

    for(int i = size - 1; i >= 0 ; --i)
    {
        for(int k = i - 1; k >= 0; --k)
        {
            m_f[k] -= m_f[i] * m_matrix[k][i];
            m_matrix[k][i] = 0;
        }
    }

    return true;
}

std::ostream &operator<< (std::ostream &out, const GaussSolver &gaussSolver)
{
    for(int i = 0; i < gaussSolver.m_f.size(); ++i)
    {
        for(int j = 0; j < gaussSolver.m_f.size(); ++j)
        {
            out << gaussSolver.m_matrix[i][j] << ' ';
        }
        out << '\t' << gaussSolver.m_f[i] << '\n';
    }

    return out;
}
