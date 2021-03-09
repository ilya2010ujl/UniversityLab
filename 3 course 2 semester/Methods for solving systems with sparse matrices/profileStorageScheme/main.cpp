#include <QCoreApplication>
#include "profilestoragescheme.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    profileStorageScheme PSS;

    PSS.readAsMatrix(std::cin);
    std::cout << '\n';
    PSS.writeAsPSS(std::cout);
    std::cout << '\n';
    PSS.writeAsMatrix(std::cout);

    return a.exec();
}
