#include <QVector>

bool solveSystem(QVector<QVector<float>> coefs, QVector<float> y, QVector<float> &result)
{
    const int systemSize = coefs.size();
    result.resize(systemSize);
    const float eps = std::numeric_limits<float>::epsilon();

    for (int rowInd = 0; rowInd < systemSize; ++rowInd) {
        float max = qAbs(coefs[rowInd][rowInd]);
        int maxElemInColInd = rowInd;

        for (int i = rowInd + 1; i < systemSize; i++) {
            if (qAbs(coefs[i][rowInd]) > max) {
              max = qAbs(coefs[i][rowInd]);
              maxElemInColInd = i;
            }
        }

        if (max < eps)
            return false;

        for (int j = 0; j < systemSize; j++) {
            float temp = coefs[rowInd][j];
            coefs[rowInd][j] = coefs[maxElemInColInd][j];
            coefs[maxElemInColInd][j] = temp;
        }

        float temp = y[rowInd];
        y[rowInd] = y[maxElemInColInd];
        y[maxElemInColInd] = temp;

        for (int i = rowInd; i < systemSize; i++) {
            float temp = coefs[i][rowInd];
            if (qAbs(temp) < eps)
                continue;

            for (int j = 0; j < systemSize; j++)
              coefs[i][j] = coefs[i][j] / temp;

            y[i] = y[i] / temp;
            if (i == rowInd)
                continue;

            for (int j = 0; j < systemSize; j++)
              coefs[i][j] -= coefs[rowInd][j];

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
