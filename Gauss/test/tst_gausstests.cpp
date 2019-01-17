#include "tst_gausstests.h"
#include <gausssolver.h>

void GaussTests::int2x2()
{
    QVector<QVector<double>> coeffs = {
        { 1, 2 },
        { 3, 4 }
    };

    QVector<double> y = { 5, 6 };

    QVector<double> result;
    QVERIFY(solveSystem(coeffs, y, result) == true);

    QCOMPARE(result[0], -4.0f);
    QCOMPARE(result[1], 4.5f);
}

void GaussTests::double2x2()
{
    QVector<QVector<double>> coeffs = {
        { 1.4f, -2.37f },
        { -0.72f, 4.31f }
    };

    QVector<double> y = { -4.81f, 6.31f };

    QVector<double> result;
    QVERIFY(solveSystem(coeffs, y, result) == true);

    QCOMPARE(result[0], -(14441.0f/10819));
    QCOMPARE(result[1], 13427.0f/10819);
}

void GaussTests::inconsistent2x2()
{
    QVector<QVector<double>> coeffs = {
        { 11.53f, 0.0f },
        { -43.27f, 0.0f }
    };

    QVector<double> y = { -4.81f, 6.31f };

    QVector<double> result;
    QVERIFY(solveSystem(coeffs, y, result) == false);
}

void GaussTests::inconsistentRealCase()
{
    QVector<QVector<double>> coeffs = {
        { 14.08f, -12.8f, -1.28f, 0.0f },
        { -12.8f, 11.52f, 0.0f, 1.28f },
        { -1.28f, 0.0f, -11.52f, 12.8f },
        {0.0f, 1.28f, 12.8f, -14.08f }
    };

    QVector<double> y = { 0.024f, 0.0f, 0.0f, -0.024f };

    QVector<double> result;
    QVERIFY(solveSystem(coeffs, y, result) == false);
}

QTEST_APPLESS_MAIN(GaussTests)
