#include <QCoreApplication>

#include <QApplication>
#include <QtMath>

#include "mainwindow.h"
#include "ExplicitGraphOfFunction/explicitgraphoffunction.h"
#include "Grid/grid.h"
#include "DiscreteFunction/discretefunction.h"

#include "rungekuttamethodforsystems.h"
#include "universaldifferentialsweepmethod.h"

int main(int argc, char *argv[])
{
    QApplication A(argc, argv);

    Camera c;
    Viewport v(&c);

    Grid grid(-1, 1, 1, -1, 0.5);
    v.addObject(&grid);

//    std::function<qreal(const qreal&)> p = [](const qreal& x) -> qreal
//    {
//        Q_UNUSED(x);
//        return 1;
//    };
//    std::function<qreal(const qreal&)> q = [](const qreal& x) -> qreal
//    {
//        Q_UNUSED(x);
//        return -2;
//    };;
//    std::function<qreal(const qreal&)> f = [](const qreal& x) -> qreal
//    {
//        Q_UNUSED(x);
//        return 0;
//    };;
//    qreal begin = 0;
//    qreal end = 1;
//    QPair<qreal, qreal> a(1,0);
//    QPair<qreal, qreal> b(0,1);
//    QPair<qreal, qreal> g(1,0);
//    QPair<qreal, qreal> fc(0,0);
//    QPair<qreal, qreal> dc(1,0);
//    int countOfSteps = 10;

//    QVector<QPair<qreal, QVector2D>> res = universalDifferentialSweepMethod(p,q,f,begin,end,a,b,g,
//                                     fc,
//                                     dc,
//                                     countOfSteps);

//    qDebug() << "\n\n";

//    for(int i = 0; i < res.size(); ++i)
//    {
//        qDebug() << res[i]
//                    << -(qExp(3 - 2 * res[i].first) - qExp(res[i].first))/(1 + 2 * qExp(3));
//    }

    const std::function<QVector<qreal>(const qreal&, const QVector<qreal>&)> f
            = [](const qreal& t, const QVector<qreal>&x) -> QVector<qreal>
    {
        return {x[0],
                x[2],
                x[0]};
    };
    QPair<qreal, QVector<qreal>>initialCondition(0, {1,2,3});
    qreal begin = 0;
    qreal end = 1;
    int countOfSteps = 10;

    QVector<QPair<qreal, QVector<qreal>>> r = rungeKuttaMethodForSystem(f, initialCondition, begin, end, countOfSteps);

    for(int i = 0; i < r.size(); ++i)
    {
        qreal x = r[i].first;
        qDebug() << r[i] << qExp(x)
                 << 2 * x + qExp(x) + 1
                 << qExp(x) + 2;
    }

    MainWindow w(&v);
    w.show();
    return A.exec();
}
