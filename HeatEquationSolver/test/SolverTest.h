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
    CPPUNIT_TEST(allPointsAreKnown);
    CPPUNIT_TEST(minus_y_plus_five);
    CPPUNIT_TEST(border_cond_always_5);
    CPPUNIT_TEST(x2_plus_y2);
    CPPUNIT_TEST(x2_plus_y2_plus_one);
    CPPUNIT_TEST(x_plus_y_linear);
    CPPUNIT_TEST(x_plus_y_asymmetrical);
    CPPUNIT_TEST(x_plus_y);
    CPPUNIT_TEST(x_plus_y_plus_one_asymmetrical);
    CPPUNIT_TEST_SUITE_END();

protected:
    void allPointsAreKnown();
    void minus_y_plus_five();
    void border_cond_always_5();
    void x2_plus_y2();
    void x2_plus_y2_plus_one();
    void x_plus_y_linear();
    void x_plus_y_asymmetrical();
    void x_plus_y();
    void x_plus_y_plus_one_asymmetrical();

private:
    void checkSolver(const InputData& data, const QVector<double>& temp);
};
