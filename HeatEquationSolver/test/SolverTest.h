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
    CPPUNIT_TEST(test3x3Linear);
    CPPUNIT_TEST_SUITE_END();

protected:
    void testAllPointsAreKnown();
    void test3x3Linear();

private:
    void checkSolver(const InputData& data, const QVector<float>& temp);
};
