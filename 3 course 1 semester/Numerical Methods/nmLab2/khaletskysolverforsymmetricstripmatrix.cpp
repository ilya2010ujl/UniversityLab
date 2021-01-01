#include "khaletskysolverforsymmetricstripmatrix.h"

#include <QtGlobal>

bool KhaletskySolverForSymmetricStripMatrix::Solve(SymmetricStripMatrix matrix,
                                                   const vector<double> &result,
                                                   vector<double> &answer,
                                                   bool needToPrintResult)
{
    int size = matrix.GetLength();
    double** LowerTriangularMatrix = new double*[size];

    answer.resize(size);

    for (int index = 0; index < size; index++)
    {
        answer[index] = 0;
    }

    for (int index = 0; index < size; index++)
    {
        LowerTriangularMatrix[index] = new double[size];

        for (int j = 0; j < size; j++)
        {
            LowerTriangularMatrix[index][j] = 0;
        }
    }

    for (int index = 0; index < size; index ++)
    {
        for (int j = 0; j <= index; j++)
        {
            double summ = 0;

            for (int k = 0; k < index; k++)
            {
                if (LowerTriangularMatrix[k][k] == 0)
                {
                    return false;
                }
                summ += LowerTriangularMatrix[index][k] * LowerTriangularMatrix[j][k] / LowerTriangularMatrix[k][k];
            }
            LowerTriangularMatrix[index][j] = matrix(index,j) - summ;
        }
    }

    double* y = new double[size];

    for (int index = 0; index < size; index++)
    {
        double summ = 0;
        for (int k = 0; k < index; k++)
        {
            summ += LowerTriangularMatrix[index][k] * y[k];
        }

        if (LowerTriangularMatrix[index][index] == 0)
        {
            return false;
        }

        y[index] = (result[index] - summ)/LowerTriangularMatrix[index][index];
    }

    for (int index = size - 1; index >= 0; index--)
    {
        double summ = 0;
        for (int k = index + 1; k < size; k++)
        {
            summ += LowerTriangularMatrix[k][index] * answer[k];
        }

        if (LowerTriangularMatrix[index][index] == 0)
        {
            return false;
        }

        answer[index] = y[index] - summ/LowerTriangularMatrix[index][index];
    }

    if (needToPrintResult)
    {
        PrintEquation(matrix, result, answer);
    }

    for (int index = 0; index < size; index++)
    {
        delete[] LowerTriangularMatrix[index];
    }

    delete[] LowerTriangularMatrix;
    delete[] y;

    return true;
}

bool KhaletskySolverForSymmetricStripMatrix::Solve(SymmetricStripMatrix matrix,
                                                   vector<double> expectedAnswer,
                                                   vector<double> &answer,
                                                   double &error,
                                                   bool needToPrintResult)
{
    int size = matrix.GetLength();

    vector<double> result;
    result.resize(0);

    for (int index = 0; index < size; index ++)
    {
        double summ = 0;
        for(int jndex = 0; jndex < size; jndex++)
        {
            summ += matrix(index, jndex) * expectedAnswer[jndex]; //вычисляю вектор ответа для заданного x
        }

        result.push_back(summ);
    }

    bool isEnded = Solve(matrix, result, answer, needToPrintResult);
    error = CountError(matrix, expectedAnswer, answer);

    return isEnded;
}



double KhaletskySolverForSymmetricStripMatrix::CountError(SymmetricStripMatrix matrix,
                                                          vector<double> expectedAnswer,
                                                          const vector<double> &answer)
{
    double q = 0.01;
    int size = matrix.GetLength();
    double relativeError = 0;


    for (int index = 0; index < size; index++)
    {
        double potentialRelativeError;
        if (expectedAnswer[index] < q)
        {
            potentialRelativeError = qAbs(answer[index] - expectedAnswer[index]);
        }
        else
        {
            potentialRelativeError = qAbs((answer[index] - expectedAnswer[index])/expectedAnswer[index]);
        }

        relativeError = std::max(relativeError, potentialRelativeError);
    }
    return relativeError;
}


void KhaletskySolverForSymmetricStripMatrix::PrintEquation(SymmetricStripMatrix matrix,
                                                           const vector<double> &result,
                                                           const vector<double> &answer)
{
    int size = matrix.GetLength();
    for (int index = 0; index < size; index++)
    {
        for (int jndex = 0; jndex < size; jndex++)
        {
            cout << matrix(index, jndex)<< " ";
        }

        cout << " || " << answer[index] << " || " << result[index] << endl;
    }
}
//вариант 3
