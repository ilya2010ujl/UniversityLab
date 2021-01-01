#include <iostream>
#include "symmetricstripmatrix.h"
#include "khaletskysolverforsymmetricstripmatrix.h"
#include <QTextCodec>
#include <QDebug>
using namespace std;

// создать плохо обусловленную матрицу
SymmetricStripMatrix CreateBadConditionedMatrix(int size, int widht, int k)
{
    double maxInMatrix = 10.1;
    double** L = new double* [size];
    double** U = new double* [size];

    for (int index = 0; index < size; index++)
    {
        L[index] = new double[size];
        U[index] = new double[size];
    }

    for (int index = 0; index < size; index ++)
    {
        for (int jndex = 0; jndex <= index; jndex++)
        {
            L[index][jndex] = static_cast<double>(rand()) /
                    static_cast<double>(RAND_MAX) * (maxInMatrix + maxInMatrix) - maxInMatrix;
            U[jndex][index] = static_cast<double>(rand()) /
                    static_cast<double>(RAND_MAX) * (maxInMatrix + maxInMatrix) - maxInMatrix;

            if (jndex != index)
            {
                L[jndex][index] = 0;
                U[index][jndex] = 0;
            }
        }
    }

    // делаем матрицу плохо обусловленной
    for (int index = 0; index < size; index++)
    {
        for (int counter = 0; counter < k; counter++)
        {
            L[index][index] /= 10;
            U[index][index] /= 10;
        }
    }

    vector<vector<double>> array;
    array.resize(size);

    for (int index = 0; index < size; index++)
    {
        array[index].resize(widht);
    }

    for (int index = 0; index < size; index++)
    {
        for (int jndex = index; jndex < widht + index; jndex++)
        {
            if (jndex >= size)
            {
                array[index][jndex - index] = 0;
            }
            else
            {
                double summ = 0;

                for (int tempIterator = 0; tempIterator < size; tempIterator++)
                {
                    summ += L[index][tempIterator] * U[tempIterator][jndex];
                }

                array[index][jndex - index] = summ;
            }
        }
    }

    for (int index = 0; index < size; index++)
    {
        delete[] L[index];
        delete[] U[index];
    }

    delete[] L;
    delete[] U;

    qDebug() << array;
    SymmetricStripMatrix matrix(widht, size, array);
    return matrix;
}

int main()
{
#ifdef Q_OS_WIN32
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
#endif

#ifdef Q_OS_LINUX
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif

    int maxInMatrix;
    int length;
    int width;

    KhaletskySolverForSymmetricStripMatrix solver;

    cout << QString::fromUtf8("- Решение симметричных ленточных матриц методом Халецкого - \n").toLocal8Bit().data();

    for (int size = 10; size <=100; size *= 10)
    {
        double averageError = 0;
        for (int index = 0; index < 4; index++)
        {
            vector<double> answer;
            vector<double> expectedAnswer;
            double error = 0;
            length = size;
            width = size / 10;
            maxInMatrix = 10;

            for (int index = 0; index < length; index ++)
            {
                expectedAnswer.push_back(1);
            }

            SymmetricStripMatrix A(width,length, maxInMatrix);
            solver.Solve(A, expectedAnswer,  answer, error);
            averageError += error;
        }
        averageError /= 4;

        cout << QString::fromUtf8("\nРазмерность: ").toLocal8Bit().data() << size
             << QString::fromUtf8(", Отношение L/N: 1/10\nСредняя относительная погрешность решения: ").toLocal8Bit().data()
             << averageError;
        averageError = 0;

        for (int index = 0; index < 4; index++)
        {
            vector<double> answer;
            vector<double> expectedAnswer;
            double error = 0;
            length = size;
            width = size / 4;
            maxInMatrix = 10;

            for (int index = 0; index < length; index ++)
            {
                expectedAnswer.push_back(1);
            }

            SymmetricStripMatrix A(width,length, maxInMatrix);
            solver.Solve(A, expectedAnswer,  answer, error);
            averageError += error;
        }
        averageError /= 4;

        cout << QString::fromUtf8("\nРазмерность: ").toLocal8Bit().data() << size
             << QString::fromUtf8(", Отношение L/N: 1/4\nСредняя относительная погрешность решения: ").toLocal8Bit().data()
             << averageError;
    }

    cout << QString::fromUtf8("\n- (Это решения при случайной генерации матриц,"
                              " поэтому матрицы в большинстве случаев хорошо обусловлены) - \n")
            .toLocal8Bit().data();

    cout<<QString::fromUtf8("\n- Решение плохо обусловленных матриц -").toLocal8Bit().data();
    length = 10;
    for (int index = 0; index < 2; index++)
    {

        for (int k = 2; k <= 6; k += 2)
        {
            double averageError = 0;
            for (int iterator = 0; iterator < 4; iterator++)
            {
                vector<double> answer;
                vector<double> expectedAnswer;

                SymmetricStripMatrix matrix = CreateBadConditionedMatrix(10, 4, k);
                double error = 0;

                for (int index = 0; index < length; index ++)
                {
                    expectedAnswer.push_back(1);
                }

                solver.Solve(matrix, expectedAnswer,  answer, error);
                averageError += error;
            }
            averageError /= 4;
            cout << QString::fromUtf8("\nРазмерность: ").toLocal8Bit().data() << length
                 << QString::fromUtf8(", k = ").toLocal8Bit().data()<< k
                 << QString::fromUtf8("\nСредняя относительная погрешность: ").toLocal8Bit().data() << averageError;
        }
        length *= 10;
    }

    cout << '\n';

    return 0;
}
