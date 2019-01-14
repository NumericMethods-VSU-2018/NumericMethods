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
        // U = 5 - y
        {
            {0, 5},
            {1, 5},
            {2, 5},

            {3, 4},
            {5, 4},

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

void SolverTest::test3x3SimetricalOneValue()
{
    InputData data = {
        {1, 1}, {1, 1}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y) { return 1; }, // k_x
        [](Coord x, Coord y) { return 1; }, // k_y
        [](Coord x, Coord y) { return 0; }, // f
        [](Coord x, Coord y) { return 99; }, // phi unused
        // U = 5 - y
        {
            {0, 5},
            {1, 5},
            {2, 5},

            {3, 5},
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
    InputData data = {
        {1, 1}, {1, 1}, // hx, hy
        -1, -1,     // origin
        [](Coord x, Coord y){ return 1; }, // k_x
        [](Coord x, Coord y){ return 1; }, // k_y
        [](Coord x, Coord y){ return 4; }, // f
        [](Coord x, Coord y){ return 0; }, // phi unused
        // U = x^2 + y^2
        {
            {0, 2},
            {1, 1},
            {2, 2},
            {3, 1},
            {5, 1},
            {6, 2},
            {7, 1},
            {8, 2},
        }
    };

    QVector<float> correctTemp = {
        2, 1,    2,
        1, 1.25, 1,
        2, 1,    2
    };
    checkSolver(data, correctTemp);
}

void SolverTest::test3x3Quad2()
{
    InputData data = {
        {1, 1}, {1, 1}, // hx, hy
        -1, -1,     // origin
        [](Coord x, Coord y){ return 1; }, // k_x
        [](Coord x, Coord y){ return 1; }, // k_y
        [](Coord x, Coord y){ return 4; }, // f
        [](Coord x, Coord y){ return 0; }, // phi unused
        // U = x^2 + y^2 + 1
        {
            {0, 3},
            {1, 2},
            {2, 3},
            {3, 2},
            {5, 2},
            {6, 3},
            {7, 2},
            {8, 3},
        }
    };

    QVector<float> correctTemp = {
        3, 2,    3,
        2, 2.25, 2,
        3, 2,    3
    };
    checkSolver(data, correctTemp);
}

// U = x + y
void SolverTest::x_plus_y_linear()
{
    InputData data = {
        {1, 3}, {1, 3}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y){ return x; }, // k_x
        [](Coord x, Coord y){ return y; }, // k_y
        [](Coord x, Coord y){ return 2; }, // f
        [](Coord x, Coord y){ return 0; }, // phi unused
        {
            {0, 0},
            {1, 1},
            {2, 4},
            {3, 1},
            {5, 5},
            {6, 4},
            {7, 5},
            {8, 8},
        }
    };

    QVector<float> correctTemp = {
        0, 1, 4,
        1, 2, 5,
        4, 5, 8
    };
    checkSolver(data, correctTemp);
}

// U = x + y
void SolverTest::x_plus_y()
{
    InputData data = {
        {1, 3}, {1, 3}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y){ return 1; }, // k_x
        [](Coord x, Coord y){ return 1; }, // k_y
        [](Coord x, Coord y){ return 0; }, // f
        [](Coord x, Coord y){ return 0; }, // phi unused
        {
            {0, 0},
            {1, 1},
            {2, 4},
            {3, 1},
            {5, 5},
            {6, 4},
            {7, 5},
            {8, 8},
        }
    };

    QVector<float> correctTemp = {
        0, 1, 4,
        1, 2, 5,
        4, 5, 8
    };
    checkSolver(data, correctTemp);
}

// U = x + y + 1
void SolverTest::x_plus_y_plus_one()
{
    InputData data = {
        {0.5, 1.5}, {0.5, 1.5}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y){ return 1; }, // k_x
        [](Coord x, Coord y){ return 1; }, // k_y
        [](Coord x, Coord y){ return 0; }, // f
        [](Coord x, Coord y){ return 0; }, // phi unused
        {
            {0, 1},
            {1, 1.5},
            {2, 3},
            {3, 1.5},
            {5, 3.5},
            {6, 3},
            {7, 3.5},
            {8, 5},
        }
    };

    QVector<float> correctTemp = {
        1,   1.5, 3,
        1.5, 2,   3.5,
        3,   3.5, 5
    };
    checkSolver(data, correctTemp);
}

void SolverTest::checkSolver(const InputData& data,
    const QVector<float>& correctTemp)
{
    HeatEquationSolver solver(data);
    CPPUNIT_ASSERT(solver.valid());
    QVector<float> actualTemp = solver.temperatures();
    auto a = actualTemp.toStdVector();
    auto c = correctTemp.toStdVector();
    CPPUNIT_ASSERT_EQUAL(correctTemp.size(), actualTemp.size());
    for (int i = 0; i < correctTemp.size(); ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(correctTemp[i], actualTemp[i], 1e-5);
    }
}
