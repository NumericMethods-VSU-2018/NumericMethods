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
        [](Coord x, Coord y) { return 5; }, // phi
        { }
    };

    QVector<double> correctTemp = {
        5, 5,
        5, 5
    };
    checkSolver(data, correctTemp);
}

void SolverTest::minus_y_plus_five()
{
    InputData data = {
        {1, 1}, {1, 1}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y) { return 1; }, // k_x
        [](Coord x, Coord y) { return 1; }, // k_y
        [](Coord x, Coord y) { return 0; }, // f
        [](Coord x, Coord y) { return 5 - y; }, // phi
        {
        }
    };

    QVector<double> correctTemp = {
        5, 5, 5,
        4, 4, 4,
        3, 3, 3
    };
    checkSolver(data, correctTemp);
}

void SolverTest::border_cond_always_5()
{
    InputData data = {
        {1, 1}, {1, 1}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y) { return 1; }, // k_x
        [](Coord x, Coord y) { return 1; }, // k_y
        [](Coord x, Coord y) { return 0; }, // f
        [](Coord x, Coord y) { return 5; }, // phi
        { }
    };

    QVector<double> correctTemp = {
        5, 5, 5,
        5, 5, 5,
        5, 5, 5
    };
    checkSolver(data, correctTemp);
}

void SolverTest::x2_plus_y2()
{
    InputData data = {
        {1, 1}, {1, 1}, // hx, hy
        -1, -1,     // origin
        [](Coord x, Coord y){ return 1; }, // k_x
        [](Coord x, Coord y){ return 1; }, // k_y
        [](Coord x, Coord y){ return 4; }, // f
        [](Coord x, Coord y){ return x*x + y*y; }, // phi
        { }
    };

    QVector<double> correctTemp = {
        2, 1, 2,
        1, 1, 1,
        2, 1, 2
    };
    checkSolver(data, correctTemp);
}

void SolverTest::x2_plus_y2_plus_one()
{
    InputData data = {
        {1, 1}, {1, 1}, // hx, hy
        -1, -1,     // origin
        [](Coord x, Coord y){ return 1; }, // k_x
        [](Coord x, Coord y){ return 1; }, // k_y
        [](Coord x, Coord y){ return 4; }, // f
        [](Coord x, Coord y){ return x*x + y*y + 1; }, // phi
        { }
    };

    QVector<double> correctTemp = {
        3, 2, 3,
        2, 2, 2,
        3, 2, 3
    };
    checkSolver(data, correctTemp);
}

void SolverTest::x_plus_y_linear()
{
    InputData data = {
        {1, 3}, {1, 3}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y){ return x; }, // k_x
        [](Coord x, Coord y){ return y; }, // k_y
        [](Coord x, Coord y){ return 2; }, // f
        [](Coord x, Coord y){ return x + y; }, // phi
        { }
    };

    QVector<double> correctTemp = {
        0, 1, 4,
        1, 2, 5,
        4, 5, 8
    };
    checkSolver(data, correctTemp);
}

void SolverTest::x_plus_y_asymmetrical()
{
    InputData data = {
        {1, 3}, {1, 3}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y){ return 1; }, // k_x
        [](Coord x, Coord y){ return 1; }, // k_y
        [](Coord x, Coord y){ return 0; }, // f
        [](Coord x, Coord y){ return x + y; }, // phi
        { }
    };

    QVector<double> correctTemp = {
        0, 1, 4,
        1, 2, 5,
        4, 5, 8
    };
    checkSolver(data, correctTemp);
}

void SolverTest::x_plus_y()
{
    InputData data = {
        {1, 1}, {1, 1}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y){ return 1; }, // k_x
        [](Coord x, Coord y){ return 1; }, // k_y
        [](Coord x, Coord y){ return 0; }, // f
        [](Coord x, Coord y){ return x + y; }, // phi
        { }
    };

    QVector<double> correctTemp = {
        0, 1, 2,
        1, 2, 3,
        2, 3, 4
    };
    checkSolver(data, correctTemp);
}

void SolverTest::x_plus_y_plus_one_asymmetrical()
{
    InputData data = {
        {0.5, 1.5}, {0.5, 1.5}, // hx, hy
        0, 0,     // origin
        [](Coord x, Coord y){ return 1; }, // k_x
        [](Coord x, Coord y){ return 1; }, // k_y
        [](Coord x, Coord y){ return 0; }, // f
        [](Coord x, Coord y){ return x + y + 1; }, // phi
        { }
    };

    QVector<double> correctTemp = {
        1,   1.5, 3,
        1.5, 2,   3.5,
        3,   3.5, 5
    };
    checkSolver(data, correctTemp);
}

void SolverTest::checkSolver(const InputData& data,
    const QVector<double>& correctTemp)
{
    HeatEquationSolver solver(data);
    CPPUNIT_ASSERT(solver.valid());
    QVector<double> actualTemp = solver.temperatures();
    auto a = actualTemp.toStdVector();
    auto c = correctTemp.toStdVector();
    CPPUNIT_ASSERT_EQUAL(correctTemp.size(), actualTemp.size());
    for (int i = 0; i < correctTemp.size(); ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(correctTemp[i], actualTemp[i], 1e-5);
    }
}
