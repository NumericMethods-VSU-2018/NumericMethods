/**
 * Nx, Ny - количество точек разбиения по направлению x,y
 * hx[0 .. Nx-1], hy[0 .. Ny-1] - и массивы шагов по x,y.
 * XO, YO -- координата левого нижнего угла прямоугольной области
 * k_x(x,y), k_y(x,y), f(x,y) -- коэффициенты уравнения
 * phi(x,y) -- функция, задающая граничное условие.
 */

#include "ParserTest.h"
#include "parser.h"

void ParserTest::parseInput1()
{
    const std::string input = "\
        0 0 \
        0 0 \
        const 12345 \
        const 23456 \
        const 34567 \
        const 45678";

    InputData data = testInput(input,
            {}, {},
            0.0f, 0.0f);

    CPPUNIT_ASSERT_EQUAL(data.k_x(0, 0), 12345.0f);
    CPPUNIT_ASSERT_EQUAL(data.k_x(1, 2), 12345.0f);

    CPPUNIT_ASSERT_EQUAL(data.k_y(0, 0), 23456.0f);
    CPPUNIT_ASSERT_EQUAL(data.k_y(2, 1), 23456.0f);

    CPPUNIT_ASSERT_EQUAL(data.f(0, 0), 34567.0f);
    CPPUNIT_ASSERT_EQUAL(data.f(3, 3), 34567.0f);

    CPPUNIT_ASSERT_EQUAL(data.phi(0, 0), 45678.0f);
    CPPUNIT_ASSERT_EQUAL(data.phi(9, 5), 45678.0f);
}

void ParserTest::parseInput2()
{
    const std::string input = "\
        3 4 \
        11 12 13 \
        1  2  3  4 \
        88 99 \
        const 123 \
        linear 2 3 4 \
        linear 2 1 5 \
        quad 1 2 3 4 5";

    InputData data = testInput(input,
            {11.0f, 12.0f, 13.0f},
            {1.0f, 2.0f, 3.0f, 4.0f},
            88.0f, 99.0f);

    CPPUNIT_ASSERT_EQUAL(data.k_x(0, 0), 123.0f);
    CPPUNIT_ASSERT_EQUAL(data.k_x(9, 8), 123.0f);

    CPPUNIT_ASSERT_EQUAL(data.k_y(0, 0), 4.0f);
    CPPUNIT_ASSERT_EQUAL(data.k_y(1, 1), 9.0f);
    CPPUNIT_ASSERT_EQUAL(data.k_y(2, 1), 11.0f);

    CPPUNIT_ASSERT_EQUAL(data.f(0, 0), 5.0f);
    CPPUNIT_ASSERT_EQUAL(data.f(1, 0), 7.0f);
    CPPUNIT_ASSERT_EQUAL(data.f(0, 1), 6.0f);

    // 1*x*x + 2*x + 3*y*y + 4*y + 5
    CPPUNIT_ASSERT_EQUAL(data.phi(0, 0), 5.0f);
    CPPUNIT_ASSERT_EQUAL(data.phi(1, 0), 8.0f);
    CPPUNIT_ASSERT_EQUAL(data.phi(1, 2), 28.0f);
}

InputData ParserTest::testInput(const std::string& input,
        std::vector<CoordDiff> hx,
        std::vector<CoordDiff> hy,
        Coord x0, Coord y0)
{
    InputData data = parseInput(input);

    CPPUNIT_ASSERT_EQUAL(data.hx.size(), hx.size());
    CPPUNIT_ASSERT_EQUAL(data.hy.size(), hy.size());

    for (size_t i = 0; i < hx.size(); ++i)
        CPPUNIT_ASSERT_EQUAL(data.hx[i], hx[i]);

    for (size_t i = 0; i < hy.size(); ++i)
        CPPUNIT_ASSERT_EQUAL(data.hy[i], hy[i]);

    CPPUNIT_ASSERT_EQUAL(data.x0, x0);
    CPPUNIT_ASSERT_EQUAL(data.y0, y0);

    return data;
}
