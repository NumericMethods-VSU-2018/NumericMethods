#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "heatequationsolver.h"

class SolverTest : public CppUnit::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(SolverTest);
    CPPUNIT_TEST(allPointsAreKnown);
    CPPUNIT_TEST_SUITE_END();

protected:
    void allPointsAreKnown();
};
