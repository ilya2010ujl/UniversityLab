#include <iostream>
#include <cassert>
#include "symmetricstripmatrix.h"

SymmetricStripMatrix::SymmetricStripMatrix(int width, int lenght, vector<vector<double>> array) : m_width(width), m_lenght(lenght)
{
    vector<vector<double>> array1;

    for (int IndexOfRow = 0; IndexOfRow < m_lenght; IndexOfRow++)
    {
        vector<double> R;

        for (int IndexOfColumn = 0; IndexOfColumn < m_width; IndexOfColumn++)
        {
            R.push_back(array[IndexOfRow][IndexOfColumn]);
        }

        m_array.push_back(R);
    }
}

SymmetricStripMatrix::SymmetricStripMatrix(int width, int lenght, double maxInMatrix)
{
    m_lenght = lenght;
    m_width = width;

    for (int IndexOfRow = 0; IndexOfRow < m_lenght; IndexOfRow++)
    {
        vector<double> R;

        double temp;

        for (int IndexOfColumn = 0; IndexOfColumn < m_width; IndexOfColumn++)
        {
            temp = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxInMatrix + maxInMatrix) - maxInMatrix;
            R.push_back(temp);
        }

        m_array.push_back(R);
    }
}

SymmetricStripMatrix::SymmetricStripMatrix()
{
    m_width = 0;
    m_lenght = 0;
}

double SymmetricStripMatrix:: operator()(int row, int column) const
{
    assert((row < m_lenght)&&(row >= 0));
    assert((column < m_lenght) && (column >= 0));

    int NewRow, NewColumn;
    if (column >= row)
    {
        NewRow = row;
        NewColumn = column - row;
    }
    else
    {
        NewRow = column;
        NewColumn = row - column;
    }

    if (NewColumn >= m_width)
    {
        return 0;
    }

    return m_array[NewRow][NewColumn];

}

std::ostream& operator<< (std::ostream &out, const SymmetricStripMatrix &Matrix)
{
    for (int index = 0; index < Matrix.m_lenght; index++)
    {
        for (int jndex = 0; jndex < Matrix.m_lenght; jndex++)
        {
            out << Matrix(index,jndex);
        }
        out<< '\n';
    }

    return out;
}
