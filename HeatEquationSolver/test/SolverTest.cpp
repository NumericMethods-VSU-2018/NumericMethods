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

void SolverTest::test3x3Linear()
{
    /* 6 7 8
     * 3 4 5
     * 0 1 2
     */
    InputData data = {
        {1, 1}, {1, 1}, // hx, hy
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
            //{4, -}, center is not specified
            {5, 5},

            {6, 5},
            {7, 5},
            {8, 5},
        }
    };

    QVector<float> correctTemp = {
        5, 5, 5,
        5, 5, 5,
        5, 5, 5
    };
    checkSolver(data, correctTemp);
}

void SolverTest::checkSolver(const InputData& data,
    const QVector<float>& correctTemp)
{
    HeatEquationSolver solver(data);
    QVector<float> actualTemp = solver.temperatures();
    CPPUNIT_ASSERT_EQUAL(correctTemp.size(), actualTemp.size());
    for (int i = 0; i < correctTemp.size(); ++i) {
        CPPUNIT_ASSERT_EQUAL(correctTemp[i], actualTemp[i]);
    }
}