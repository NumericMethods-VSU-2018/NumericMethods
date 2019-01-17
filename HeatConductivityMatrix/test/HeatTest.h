#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "HeatMatrix.h"

class InputData;

template<class T>
class QVector;

class HeatTest : public CppUnit::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(HeatTest);
    CPPUNIT_TEST(integrateTest);
    CPPUNIT_TEST_SUITE_END();

protected:
    void integrateTest();

private:
    void integrateTest(const Point& a, const Point& b, const Point& c, 
        const MathFunc& f, double expected);
};
