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
        return qTan(x) - x;
        // return -x + qExp(x) - 1; // y(0) = 0
        // return -x + 2 * qExp(x - 1) - 1; // y(1) = 0
        // return -x - 1; // y(-1) = 0

        // return 2 * qAtan(tanh((x * x - 1) / 4));
    };

    ExplicitGraphOfFunction Graph(exactSolution, 0.1, 0, 1);
    Graph.setColor(QColorConstants::Red);
    v.addObject(&Graph);

    std::function<qreal(const QVector2D&)> f = [](const QVector2D& x) -> qreal
    {
        return (x.y() + x.x()) * (x.y() + x.x());
    };

    QVector<QVector2D> R34 = rungeKuttaMethodDoublingHalvingStep(f, QVector2D(0,0), 0, 1, 0.0001, 0.0001);

    DiscreteFunction D34(R34);
    D34.setColor(QColorConstants::Green);
    v.addObject(&D34);

    MainWindow w(&v);
    w.show();
    return a.exec();
}
