#include "ReorderTest.h"
#include "ReorderMatrix.h"

#include <algorithm>

/*
  Simple matrix

  Before reorder:
  0 - 1 - 2
  | \ | \ |
  3 - 4 - 5
  | \ | \ |
  6 - 7 - 8

  After reorder:
  5 - 2 - 0
  | \ | \ |
  7 - 4 - 1
  | \ | \ |
  8 - 6 - 3
*/

const Matrix simpleMatrixBeforeReorder = {
    {1, 1, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 0, 0, 0},
    {1, 0, 0, 1, 1, 0, 1, 1, 0},
    {1, 1, 0, 1, 1, 1, 0, 1, 1},
    {0, 1, 1, 0, 1, 1, 0, 0, 1},
    {0, 0, 0, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 1, 1, 0, 1, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 1, 1},
};

const Reorder simpleMatrixNewOrder = { 
    6, 3, 7, 0, 4, 8, 1, 5, 2
};

const Matrix simpleMatrixAfterReorder = {
    {1, 1, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 0, 1, 1, 0, 0, 0},
    {0, 1, 0, 1, 1, 0, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 0, 1, 1, 0, 1, 0},
    {0, 0, 0, 1, 1, 0, 1, 1, 1},
    {0, 0, 0, 0, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 1, 1, 1},
};

void ReorderTest::testSimpleMatrixReorder()
{
    Reorder newOrder = getReorder(simpleMatrixBeforeReorder);
    {
        const Reorder& actual = newOrder;
        const Reorder& expected = simpleMatrixNewOrder;
        assertVectorEqual(expected, actual);
    }

    Matrix reordered = reorder(simpleMatrixBeforeReorder, newOrder);
    {
        const Matrix& actual = reordered;
        const Matrix& expected = simpleMatrixAfterReorder;
        assertMatrixEqual(expected, actual);
    }
}

void ReorderTest::test2x2Reorder()
{
    Matrix input = {
        {1, 2},
        {3, 4}
    };

    // Same order
    Matrix output = reorder(input, {0, 1});
    assertMatrixEqual(input, output);

    // Not same order
    Matrix expected = {
        {4, 3},
        {2, 1}
    };
    Matrix output2 = reorder(input, {1, 0});
    assertMatrixEqual(expected, output2);
}

void ReorderTest::testVectorReorder()
{
    Vector input = { 0, 1, 2, 3, 4, 5 };
    Reorder r       = { 4, 2, 0, 1, 3, 5 };
    Vector expected = { 4, 2, 0, 1, 3, 5 };
    Vector actual = reorder(input, r);
    assertVectorEqual(expected, actual);
}

void ReorderTest::testRestoreVector()
{
    size_t size = 6;
    Vector input(size);
    std::generate(input.begin(), input.end(), rand);
    Reorder r(size);
    for (size_t i = 0; i < size; i++) {
        r[i] = i;
    }

    std::random_shuffle(r.begin(), r.end());

    Vector output = restoreOrder(reorder(input, r), r);
    assertVectorEqual(input, output);
}

void ReorderTest::assertMatrixEqual(const Matrix& a, const Matrix& b)
{
    CPPUNIT_ASSERT_EQUAL(a.size(), b.size());
    for (size_t i = 0; i < a.size(); i++) {
        assertVectorEqual(a[i], b[i]);
    }
}