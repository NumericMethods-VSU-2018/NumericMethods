#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using Matrix = std::vector<std::vector<int>>;

class BandMatrixTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE(BandMatrixTest);
    CPPUNIT_TEST(test2x2Matrix);
    CPPUNIT_TEST(test4x4Matrix);
    CPPUNIT_TEST(testNonOptimal);
    CPPUNIT_TEST_SUITE_END();

protected:
    void test2x2Matrix();
    void test4x4Matrix();
    void testNonOptimal();

private:
    void testBandMatrix(const Matrix& input, const Matrix& actual);
};
