#ifndef SymmetricStripMatrix_hpp
#define SymmetricStripMatrix_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class SymmetricStripMatrix
{
public:
    SymmetricStripMatrix(int width, int lenght, vector<vector<double>> array);
    SymmetricStripMatrix(int width, int lenght, double maxInMatrix = 100.1);
    SymmetricStripMatrix();

    int GetLength()
    {
        return m_lenght;
    }

    double operator()(int row, int column) const;

private:
    int m_width;
    int m_lenght;
    vector<vector<double>> m_array;

    friend std::ostream& operator<< (std::ostream &out, const SymmetricStripMatrix &Matrix);
};

#endif /* SymmetricStripMatrix_hpp */
