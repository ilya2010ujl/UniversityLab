#include <QCoreApplication>
#include "adjacencymatrix.h"
#include <fstream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    adjacencyMatrix m;
    std::ifstream ifs("matrix.txt");

    m.readMatrix(ifs);
    m.writeMatrix(std::cout);

    std::cout << "Cathill:\n";
    m.reduceWidthTape();

    std::ofstream ofs("reduceMatrix.txt");
    m.writeMatrix(std::cout);
    m.writeMatrix(ofs);
    ofs.close();

    return a.exec();
}
