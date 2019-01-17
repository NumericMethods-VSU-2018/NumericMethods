#ifndef GAUSSSOLVER_H
#define GAUSSSOLVER_H

#include <QVector>

bool solveBandSystem(QVector<QVector<double>> coefs, QVector<double> y, QVector<double> &result);
bool solveSystem(QVector<QVector<double>> coefs, QVector<double> y, QVector<double> &result);

#endif // GAUSSSOLVER_H
