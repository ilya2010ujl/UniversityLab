#include <QCoreApplication>
#include "adjacencymatrix.h"
#include <fstream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    adjacencyMatrix m;
    std::ifstream ifs("matrix2.txt");

    m.readMatrix(ifs);
    m.writeMatrix(std::cout);

    std::cout << "Cathill:\n";
    m.reduceWidthTape();
    m.writeMatrix(std::cout);

    return a.exec();
}
