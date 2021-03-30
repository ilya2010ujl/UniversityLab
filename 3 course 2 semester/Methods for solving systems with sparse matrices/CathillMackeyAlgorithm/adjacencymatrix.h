#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include <QVector>
#include <iostream>

class adjacencyMatrix
{
public:
    void readMatrix(std::istream &is);
    void writeMatrix(std::ostream &out);
    void reduceWidthTape();

private:
    QVector<int> variables;

    qint64 m_size;
    QVector<QVector<double>> m_adjacencyMatrix;
};

#endif // ADJACENCYMATRIX_H
