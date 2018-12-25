#ifndef GAUSSSOLVER_H
#define GAUSSSOLVER_H

#include <QVector>

bool solveSystem(QVector<QVector<float>> coefs, QVector<float> y, QVector<float> &result);

#endif // GAUSSSOLVER_H
