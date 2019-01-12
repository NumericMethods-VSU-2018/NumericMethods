#include "SolverTest.h"
#include "heatequationsolver.h"
#include <parser.h>

void SolverTest::allPointsAreKnown()
{
    InputData data = {
        {5}, {5}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y) { return 1; }, // k_x
        [](Coord x, Coord y) { return 1; }, // k_y
        [](Coord x, Coord y) { return 1; }, // f
        [](Coord x, Coord y) { return 99; }, // phi
        {
            {0, 5},
            {1, 5},
            {2, 5},
            {3, 5},
        }
    };

    QVector<float> correctTemp = {5, 5, 5, 5};
    HeatEquationSolver solver(data);
    QVector<float> actualTemp = solver.temperatures();
    CPPUNIT_ASSERT_EQUAL(correctTemp.size(), actualTemp.size());
    for (int i = 0; i < correctTemp.size(); ++i) {
        CPPUNIT_ASSERT_EQUAL(correctTemp[i], actualTemp[i]);
    }
}
