#include <QCoreApplication>

#include "rungekuttamethod.h"
#include <QApplication>
#include <QtMath>

#include "mainwindow.h"
#include "ExplicitGraphOfFunction/explicitgraphoffunction.h"
#include "Grid/grid.h"
#include "DiscreteFunction/discretefunction.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Camera c;
    Viewport v(&c);

    Grid grid(-1, 1, 1, -1, 0.5);
    v.addObject(&grid);

    ExplicitGraphOfFunction::Function exactSolution = [](const qreal &x) -> qreal
    {
        return -x + qExp(x) - 1;
    };

    ExplicitGraphOfFunction Graph(exactSolution, 0.1, 0, 1);
    v.addObject(&Graph);

    std::function<qreal(const QVector2D&)> f = [](const QVector2D& x) -> qreal
    {
        return x.x() + x.y();
    };

    QVector<QVector2D> R34 = methodRungeKuttaWithDoublingAndHalvingStep3rdAnd4thOrder(f, QVector2D(0,0), 0, 1, 0.2, 0.2);

    for(int i = 0 ; i < R34.size(); ++i)
    {
        qDebug() << R34[i];
    }

    DiscreteFunction D34(R34);
    D34.setColor(QColorConstants::Green);
    v.addObject(&D34);

    // создаём и открываем главное окно
    MainWindow w(&v);
    w.show();
    return a.exec();
}
