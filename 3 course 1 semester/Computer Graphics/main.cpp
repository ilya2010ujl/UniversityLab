#include <QApplication>
#include <QVector2D>

#include "mainwindow.h"
#include "Viewport/viewport.h"
#include "Point3D/point3d.h"
#include "Line3D/line3d.h"
#include "Utils/utilstests.h"

qint32 main(qint32 argc, char *argv[])
{
    QApplication a(argc, argv);

    UtilsTests utilsTests;
    QTest::qExec(&utilsTests);

    MainWindow w;

    w.show();
    return a.exec();
}
