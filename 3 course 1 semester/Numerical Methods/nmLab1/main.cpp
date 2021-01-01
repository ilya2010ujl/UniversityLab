#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include "System/system.h"
#include "utils/utils.h"
#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[])
{
    srand(static_cast<int>(time(0)));

    QCoreApplication a(argc, argv);

    QVector<double> A; // главная диагональ
    QVector<double> b; // верхняя кодиагональ
    QVector<double> c; // нижняя кодиагональ
    QVector<double> f;
    QVector<double> fIdentity;
    unsigned int WhenP; // на какой строке стоит p
    QVector<double> p; // p выше чем q
    unsigned int WhenQ; // на какой строке стоит q
    QVector<double> q;

    QVector<double> x;
    QVector<double> xIdentity;
    QVector<double> xSolve;
    QVector<double> xIdentitySolve;

    int numOfIterations = 10;
    for (int size = 10; size < 10000; size*=10)
    {
        for (int border = 10; border < 10000; border*=10)
        {
            double accuracy = 0;
            double error = 0;
            for (int iteration = 1; iteration <= numOfIterations; iteration++)
            {
                generateRandomVectorsForSystem(A, b, c, f, WhenP, p, WhenQ, q, x, size, border);
                System S(A, b, c, f, WhenP, p, WhenQ, q);
                generateRandomVectorsForSystemWhereXIdentity(A, b, c, fIdentity, WhenP, p, WhenQ, q, xIdentity, size, border);
                System SIdentity(A, b, c, fIdentity, WhenP, p, WhenQ, q);

                if(!S.solveSystem(xSolve)  || !SIdentity.solveSystem(xIdentitySolve))
                {
                    --iteration;
                    break;
                }

                accuracy += estimationOfSolutionAccuracy(xIdentity, xIdentitySolve);
                error += relativeSolutionError(x, xSolve);
            }
            accuracy /= numOfIterations;
            error /= numOfIterations;
            qDebug() << "Size: " << size << ", border: " << border << ", error: " << error << ", accuracy" << accuracy;
        }
    }

    return a.exec();
}
