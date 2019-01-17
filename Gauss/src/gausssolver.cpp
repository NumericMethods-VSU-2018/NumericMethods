#include "gausssolver.h"

bool solveBandSystem(QVector<QVector<double>> coefs, QVector<double> y, QVector<double> &result)
{
    const int L = coefs[0].size();
    QVector<QVector<double>> extended(coefs.size());
    for (int i = 0; i < extended.size(); i++) {
        extended[i].resize(coefs.size());
        for (int j = 0; j < extended[i].size(); j++)
        {
            if (j > i) {
                int modifiedInd = i - j + L - 1;
                if (modifiedInd < 0 || modifiedInd >= L)
                    extended[i][j] = 0;
                else
                    extended[i][j] = coefs[j][modifiedInd];
            } else {
                int modifiedInd = j - i + L - 1;
                if (modifiedInd < 0 || modifiedInd >= L)
                    extended[i][j] = 0;
                else
                    extended[i][j] = coefs[i][modifiedInd];
            }
        }
    }

    return solveSystem(extended, y, result);
}

bool solveSystem(QVector<QVector<double>> coefs, QVector<double> y, QVector<double> &result)
{
    const int systemSize = coefs.size();
    result.resize(systemSize);

    for (int rowInd = 0; rowInd < systemSize; ++rowInd) {
        double max = qAbs(coefs[rowInd][rowInd]);
        int maxElemInColInd = rowInd;

        for (int i = rowInd + 1; i < systemSize; i++) {
            if (qAbs(coefs[i][rowInd]) > max) {
              max = qAbs(coefs[i][rowInd]);
              maxElemInColInd = i;
            }
        }

        if (qFuzzyIsNull(max))
            return false;

        for (int j = 0; j < systemSize; j++) {
            double temp = coefs[rowInd][j];
            coefs[rowInd][j] = coefs[maxElemInColInd][j];
            coefs[maxElemInColInd][j] = temp;
        }

        double temp = y[rowInd];
        y[rowInd] = y[maxElemInColInd];
        y[maxElemInColInd] = temp;

        for (int i = rowInd; i < systemSize; i++) {
            double temp = coefs[i][rowInd];
            if (qFuzzyIsNull(temp))
                continue;

            for (int j = 0; j < systemSize; j++)
              coefs[i][j] = coefs[i][j] / temp;

            y[i] = y[i] / temp;
            if (i == rowInd)
                continue;

            for (int j = 0; j < systemSize; j++) {
                coefs[i][j] -= coefs[rowInd][j];
            }


            y[i] -= y[rowInd];
        }
    }

    for (int rowInd = systemSize - 1; rowInd >= 0; rowInd--) {
        result[rowInd] = y[rowInd];
        for (int i = 0; i < rowInd; i++)
            y[i] -= coefs[i][rowInd] * result[rowInd];
    }
    return true;
}
