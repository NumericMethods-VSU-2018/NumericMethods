#include "HeatTest.h"
#include "HeatMatrix.h"
#include <cmath>

void HeatTest::integrateTest()
{
    auto res = integrate({1, 1}, {1, 3}, {3, 1}, [](Coord x, Coord y) {
        return x;
    });

    CPPUNIT_ASSERT_DOUBLES_EQUAL(8.0 / 3, res, 1e-5);
    return;

    res = integrate({0, 0}, {0, 1}, {1, 0}, [](Coord x, Coord y) {
        return 10;
    });

    CPPUNIT_ASSERT_DOUBLES_EQUAL(5, res, 1e-5);

    res = integrate({0, 0}, {0, 2}, {2, 0}, [](Coord x, Coord y) {
        return x + y;
    });

    CPPUNIT_ASSERT_DOUBLES_EQUAL(0, res, 1e-5);

    res = integrate({0, 0}, {0, 2}, {2, 0}, [](Coord x, Coord y) {
        return x;
    });

    CPPUNIT_ASSERT_DOUBLES_EQUAL(8.0 / 3, res, 1e-5);
}

void HeatTest::integrateTest(const Point& a, const Point& b, const Point& c, 
    const MathFunc& f, double expected)
{

}