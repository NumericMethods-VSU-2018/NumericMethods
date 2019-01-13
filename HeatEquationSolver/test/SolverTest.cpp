#include "SolverTest.h"
#include "heatequationsolver.h"
#include <parser.h>

void SolverTest::testAllPointsAreKnown()
{
    InputData data = {
        {5}, {5}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y) { return 1; }, // k_x
        [](Coord x, Coord y) { return 1; }, // k_y
        [](Coord x, Coord y) { return 1; }, // f
        [](Coord x, Coord y) { return 99; }, // phi unused
        {
            {0, 5},
            {1, 5},
            {2, 5},
            {3, 5},
        }
    };

    QVector<float> correctTemp = {
        5, 5,
        5, 5
    };
    checkSolver(data, correctTemp);
}

/* 6 7 8
 * 3 4 5
 * 0 1 2
 */
void SolverTest::test3x3LinearVertical()
{
    InputData data = {
        {1, 1}, {1, 1}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y) { return 1; }, // k_x
        [](Coord x, Coord y) { return 1; }, // k_y
        [](Coord x, Coord y) { return 0; }, // f
        [](Coord x, Coord y) { return 99; }, // phi unused
        {
            {0, 5},
            {1, 5},
            {2, 5},

            {6, 3},
            {7, 3},
            {8, 3},
        }
    };

    QVector<float> correctTemp = {
        5, 5, 5,
        4, 4, 4,
        3, 3, 3
    };
    checkSolver(data, correctTemp);
}

void SolverTest::test3x3LinearDiagonal()
{
    InputData data = {
        {1, 1}, {1, 1}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y) { return 1; }, // k_x
        [](Coord x, Coord y) { return 1; }, // k_y
        [](Coord x, Coord y) { return 0; }, // f
        [](Coord x, Coord y) { return 99; }, // phi unused
        {
            {0, 10},
            {8, 0},
        }
    };

    QVector<float> correctTemp = {
        10,   6.25, 5,
        6.25, 5,    3.75,
        5,    3.75, 0,
    };
    checkSolver(data, correctTemp);
}

void SolverTest::test3x3Quad()
{
    // Doesn't work
    InputData data = {
        {1, 1}, {1, 1}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y){ return x; }, // k_x
        [](Coord x, Coord y){ return y; }, // k_y
        [](Coord x, Coord y){ return 8 * x + 12 * y; }, // f
        [](Coord x, Coord y){ return 0; }, // phi unused
        {
            {0, 0},
            {8, 10},
        }
    };

    QVector<float> correctTemp = {
        5, 5, 5,
        5, 3, 5,
        5, 5, 5
    };
    checkSolver(data, correctTemp);
}

void SolverTest::checkSolver(const InputData& data,
    const QVector<float>& correctTemp)
{
    HeatEquationSolver solver(data);
    QVector<float> actualTemp = solver.temperatures();
    auto a = actualTemp.toStdVector();
    auto c = correctTemp.toStdVector();
    CPPUNIT_ASSERT_EQUAL(correctTemp.size(), actualTemp.size());
    for (int i = 0; i < correctTemp.size(); ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(correctTemp[i], actualTemp[i], 1e-5);
    }
}