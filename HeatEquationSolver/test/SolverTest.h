#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "heatequationsolver.h"

class InputData;

template<class T>
class QVector;

class SolverTest : public CppUnit::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(SolverTest);
    CPPUNIT_TEST(testAllPointsAreKnown);
    CPPUNIT_TEST(test3x3SimetricalOneValue);
    CPPUNIT_TEST(test3x3LinearVertical);
    CPPUNIT_TEST(test3x3LinearDiagonal);
    CPPUNIT_TEST(test3x3Quad);
    CPPUNIT_TEST(test3x3Quad2);
    CPPUNIT_TEST(x_plus_y);
    CPPUNIT_TEST(x_plus_y_plus_one);
    CPPUNIT_TEST(x_plus_y_linear);
    CPPUNIT_TEST_SUITE_END();

protected:
    void testAllPointsAreKnown();
    void test3x3LinearVertical();
    void test3x3LinearDiagonal();
    void test3x3Quad();
    void test3x3Quad2();
    void test3x3SimetricalOneValue();
    void x_plus_y();
    void x_plus_y_plus_one();
    void x_plus_y_linear();

private:
    void checkSolver(const InputData& data, const QVector<float>& temp);
};
