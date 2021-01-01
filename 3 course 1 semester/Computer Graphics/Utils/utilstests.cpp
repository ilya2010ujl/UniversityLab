#include "utilstests.h"
#include "utils.h"

UtilsTests::UtilsTests(QObject *parent) : QObject(parent) {}

void UtilsTests::testdistanceFromPointToLine01()
{
    QVector3D point(1, 0, 0);
    QVector3D beginLine(3, 0, 0), endLine(3, 1, 0);
    QCOMPARE(utils::distanceFromPointToLine(point, beginLine, endLine), 2);
}

void UtilsTests::testdistanceFromPointToLine02()
{
    QVector3D point(-1, 2, 0);
    QVector3D beginLine(1, 13, 0), endLine(4, 17, 0);
    QCOMPARE(utils::distanceFromPointToLine(point, beginLine, endLine), 5);
}

void UtilsTests::testdistanceFromPointToLine03()
{
    QVector3D point(0, 2, 3);
    QVector3D beginLine(5, 2, 1), endLine(3, 1, -1);
    QCOMPARE(utils::distanceFromPointToLine(point, beginLine, endLine), 5);
}

void UtilsTests::testdistanceFromPointToLine04()
{
    QVector3D point(0, 2, 4);
    QVector3D beginLine(0, 1, 2), endLine(0, 3, 6);
    QCOMPARE(utils::distanceFromPointToLine(point, beginLine, endLine), 0);
}
