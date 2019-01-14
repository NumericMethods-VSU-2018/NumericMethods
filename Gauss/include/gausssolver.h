#ifndef GAUSSSOLVER_H
#define GAUSSSOLVER_H

#include <QVector>

bool solveBandSystem(QVector<QVector<float>> coefs, QVector<float> y, QVector<float> &result);
bool solveSystem(QVector<QVector<float>> coefs, QVector<float> y, QVector<float> &result);

#endif // GAUSSSOLVER_H
