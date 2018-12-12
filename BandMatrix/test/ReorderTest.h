#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using Matrix = std::vector<std::vector<int>>;

class ReorderTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE(ReorderTest);
    CPPUNIT_TEST(testSimpleMatrixReorder);
    CPPUNIT_TEST(test2x2Reorder);
    CPPUNIT_TEST(testVectorReorder);
    CPPUNIT_TEST(testRestoreVector);
    CPPUNIT_TEST_SUITE_END();

protected:
    void testSimpleMatrixReorder();
    void test2x2Reorder();
    void testVectorReorder();
    void testRestoreVector();

private:
    void assertMatrixEqual(const Matrix& a, const Matrix& b);

    template<class T>
    void assertVectorEqual(const std::vector<T>& a, const std::vector<T>& b)
    {
        CPPUNIT_ASSERT_EQUAL(a.size(), b.size());
        for (size_t i = 0; i < a.size(); i++) {
            CPPUNIT_ASSERT_EQUAL(a[i], b[i]);
        }
    }
};