#ifndef FIRSTORDERPARTIALDIFFERENTIALEQUATIONSOLVER_H
#define FIRSTORDERPARTIALDIFFERENTIALEQUATIONSOLVER_H

#include <QVector>
#include <functional>

QVector<QVector<qreal>> firstOrderPartialDifferentialEquationSolver(
        const std::function<qreal(const qreal& x, const qreal& t)> &f,
        const qreal &c,
        const qreal &a,
        const qreal &b,
        const std::function<qreal(const qreal &x)> &phi,
        const std::function<qreal(const qreal &t)> &csi,
        const qreal &T,
        const int& countHorizontalSteps,
        const int& countVertiacalSteps
        );

#endif // FIRSTORDERPARTIALDIFFERENTIALEQUATIONSOLVER_H
