#include "adjacencymatrix.h"

void adjacencyMatrix::readMatrix(std::istream &is)
{
    is >> m_size;

    m_adjacencyMatrix.resize(m_size);
    variables.resize(m_size);

    for(int i = 0; i < m_size; ++i)
    {
        variables[i] = i;
    }

    for(qint64 i = 0; i < m_size; ++i)
    {
        m_adjacencyMatrix[i].resize(m_size);
        for(qint64 j = 0; j < m_size; ++j)
        {
            is >> m_adjacencyMatrix[i][j];
        }
    }
}

void adjacencyMatrix::writeMatrix(std::ostream &out)
{
    out << m_size << '\n';

    for(qint64 i = 0; i < m_size; ++i)
    {
        for(qint64 j = 0; j < m_size; ++j)
        {
            out << m_adjacencyMatrix[variables[i]][variables[j]] << ' ';
        }
        out << '\n';
    }
}

void adjacencyMatrix::reduceWidthTape()
{
    QVector<int> newVariables;
    newVariables.push_back(0);

    for(int i = 0; i < m_size; ++i)
    {
        for(int j = 0; j < m_size; ++j)
        {
            if(m_adjacencyMatrix[newVariables[i]][j])
            {
                if(newVariables.indexOf(j) == -1)
                {
                    newVariables.push_back(j);
                }
            }
        }
    }

    variables = newVariables;
}
