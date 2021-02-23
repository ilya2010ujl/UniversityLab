#include <QCoreApplication>

#include "rungekuttamethod.h"
#include <QApplication>
#include <QtMath>

#include "mainwindow.h"
#include "Viewport/viewport.h"
#include "Camera/camera.h"
#include "ExplicitGraphOfFunction/explicitgraphoffunction.h"
#include "Grid/grid.h"
#include "DiscreteFunction/discretefunction.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // создаем вьюпорт и камеру
    Camera c;
    Viewport v(&c);

    // Создаём и добавляем во вьюпорт сетку
    Grid grid(-1, 1, 1, -1, 0.5);
    v.addObject(&grid);

    // создаём график функции
    ExplicitGraphOfFunction Graph(
                [](const qreal &x) -> qreal
    {
        return -x + qExp(x) - 1;
    }, 0.1, 0, 1);
    v.addObject(&Graph);

    std::function<qreal(const QVector2D&)> f = [](const QVector2D& x) -> qreal
    {
        return x.x() + x.y();
    };

    QVector<QVector2D> R = RungeKuttaMethod(f, QVector2D(0,0), 0, 1, 0.3);
    DiscreteFunction D(R);
    D.setColor(QColorConstants::Black);
    v.addObject(&D);

    // создаём и открываем главное окно
    MainWindow w(&v);
    w.show();
    return a.exec();
}
