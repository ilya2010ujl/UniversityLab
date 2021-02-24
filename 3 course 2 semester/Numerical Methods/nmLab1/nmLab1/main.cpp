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

    ExplicitGraphOfFunction::Function exactSolution = [](const qreal &x) -> qreal
    {
        return -x + qExp(x) - 1;
        // return -x + 2 * qExp(x - 1) - 1;
    };

    // создаём график функции
    ExplicitGraphOfFunction Graph(exactSolution, 0.1, 0, 1);
    v.addObject(&Graph);

    std::function<qreal(const QVector2D&)> f = [](const QVector2D& x) -> qreal
    {
        return x.x() + x.y();
    };

    QVector<QVector2D> R3 = ThirdOrderRungeKuttaMethod(f, QVector2D(0,0), 0, 1, 0.3);

    QVector<QVector2D> R4 = FourthOrderRungeKuttaMethod(f, QVector2D(0,0), 0, 1, 0.3);

    DiscreteFunction D3(R3);
    DiscreteFunction D4(R4);
    D3.setColor(QColorConstants::Black);
    D4.setColor(QColorConstants::Green);
    v.addObject(&D3);
    v.addObject(&D4);

    for(int i = 0; i < R3.size(); ++i)
    {
        qDebug() << "R3: " << R3[i];
        qDebug() << "R4: " << R4[i];

        qDebug() << "R4 - R3: "<< (R4[i] - R3[i]).y();

        qDebug() << "exactSolution - R3: " << exactSolution(R3[i].x()) - R3[i].y();
        qDebug() << "exactSolution - R4: " << exactSolution(R4[i].x()) - R4[i].y() << '\n';
    }

    // создаём и открываем главное окно
    MainWindow w(&v);
    w.show();
    return a.exec();
}
