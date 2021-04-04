#include <QCoreApplication>

#include <QApplication>
#include <QtMath>

#include "mainwindow.h"
#include "ExplicitGraphOfFunction/explicitgraphoffunction.h"
#include "Grid/grid.h"
#include "DiscreteFunction/discretefunction.h"

#include "rungekuttamethodforsystems.h"
#include "universaldifferentialsweepmethod.h"

void systemTest()
{
    const std::function<QVector<qreal>(const qreal&, const QVector<qreal>&)> f
            = [](const qreal& t, const QVector<qreal>&x) -> QVector<qreal>
    {
        Q_UNUSED(t);

        return {x[1] + t,
                x[0],
                0};
    };
    QPair<qreal, QVector<qreal>>initialCondition(0, {1,-1,1});
    qreal begin = 0;
    qreal end = 1;
    int countOfSteps = 10;

    QVector<QPair<qreal, QVector<qreal>>> r = rungeKuttaMethodForSystem(f, initialCondition, begin, end, countOfSteps);

    for(int i = 0; i < r.size(); ++i)
    {
        qreal x = r[i].first;
        qDebug() << r[i]
                 << 0.5*qExp(x)+1.5*qExp(-x)-1
                 << 0.5*qExp(x)-1.5*qExp(-x)-x
                 << 1;
    }
}

int main(int argc, char *argv[])
{
    QApplication A(argc, argv);

    Camera c;
    Viewport v(&c);

    Grid grid(-10, 10, 10, -10, 1);
    v.addObject(&grid);

    std::function<qreal(const qreal&)> y
            = [](const qreal&x) -> qreal
    {
        return 1+2*qExp(x);
    };

    std::function<qreal(const qreal&)> ySh
            = [](const qreal&x) -> qreal
    {
        return 2*qExp(x);
    };

    ExplicitGraphOfFunction Y(y, 0.0001, 0, 1);
    Y.setColor(QColorConstants::Black); // график
    v.addObject(&Y);

    ExplicitGraphOfFunction YSh(ySh, 0.0001, 0, 1);
    YSh.setColor(QColorConstants::Green); // производная
    v.addObject(&YSh);
////////////////////////////////////////
    std::function<qreal(const qreal&)> p
            = [](const qreal&x) -> qreal
    {
        Q_UNUSED(x);
        return -1;
    };
    std::function<qreal(const qreal&)> q
            = [](const qreal&x) -> qreal
    {
        Q_UNUSED(x);
        return 0;
    };
    std::function<qreal(const qreal&)> f
            = [](const qreal&x) -> qreal
    {
        Q_UNUSED(x);
        return 0;
    };
    qreal begin = 0; // a
    qreal end = 1; // b
    QPair<qreal, qreal> a(1,-1); // a1 a2
    QPair<qreal, qreal> b(1,1); // b1 b2
    QPair<qreal, qreal> g(5,1); // g1 g2
    int countOfSteps = 5;

    QVector<QPair<qreal, QVector2D>> r;

    try
    {
        r = universalDifferentialSweepMethod(p,q,f,begin,end,a,b,g,countOfSteps);
    }
    catch (QString &error)
    {
        qDebug() << error << '\n';
        return -1;
    }
    QVector<QVector2D> yd(r.size());
    QVector<QVector2D> ydSh(r.size());

    for(int i = 0; i < r.size(); ++i)
    {
        qDebug() << r[i].first << r[i].second[0] << r[i].second[1] << y(r[i].first) << ySh(r[i].first);
        yd[i][0] = r[i].first;
        ydSh[i][0] = r[i].first;
        yd[i][1] = r[i].second[0];
        ydSh[i][1] = r[i].second[1];
    }

    DiscreteFunction Yd(yd);
    Yd.setColor(QColorConstants::Red);
    v.addObject(&Yd);
    DiscreteFunction YdSh(ydSh);
    YdSh.setColor(QColorConstants::Blue);
    v.addObject(&YdSh);

    MainWindow w(&v);
    w.show();
    return A.exec();
}
