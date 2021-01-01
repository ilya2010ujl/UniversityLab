#ifndef UTILSTESTS_H
#define UTILSTESTS_H

#include <QObject>
#include <QtTest>

class UtilsTests : public QObject
{
    Q_OBJECT
public:
    explicit UtilsTests(QObject *parent = nullptr);
private slots:
    void testdistanceFromPointToLine01();
    void testdistanceFromPointToLine02();
    void testdistanceFromPointToLine03();
    void testdistanceFromPointToLine04();
};
#endif // UTILSTESTS_H
