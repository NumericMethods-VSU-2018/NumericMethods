#include "BandMatrixTest.h"
#include "BandMatrix.h"

int test()
{
    int size;
    Matrix m = create2DMatrix(size, size);
    Matrix band = buildBandMatrix(m);
    return 0;
}

void BandMatrixTest::test2x2Matrix()
{
    testBandMatrix({
        {1, 0},
        {0, 1},
    }, {
        {1},
        {1},
    });
}

void BandMatrixTest::test4x4Matrix()
{
    testBandMatrix({
        {1, 2, 0, 0},
        {2, 3, 4, 0},
        {0, 4, 5, 6},
        {0, 0, 6, 7},
    }, {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 0},
    });
}

void BandMatrixTest::testNonOptimal()
{
    testBandMatrix({
        {1, 2, 3, 4},
        {2, 3, 4, 5},
        {3, 4, 5, 6},
        {4, 5, 6, 7},
    }, {
        {1, 2, 3, 4},
        {3, 4, 5, 0},
        {5, 6, 0, 0},
        {7, 0, 0, 0},
    });
}

void BandMatrixTest::testRealExample()
{
    testBandMatrix({
        {2, 1, 0, 1, 0, 0},
        {1, 6, 1, 2, 2, 0},
        {0, 1, 2, 0, 1, 0},
        {1, 2, 0, 6, 2, 1},
        {0, 2, 1, 2, 6, 1},
        {0, 0, 0, 1, 1, 2},
    }, {
        {2, 1, 0, 1},
        {6, 1, 2, 2},
        {2, 0, 1, 0},
        {6, 2, 1, 0},
        {6, 1, 0, 0},
        {2, 0, 0, 0},
    });
}

void BandMatrixTest::testBandMatrix(const Matrix& input, const Matrix& expected)
{
    const Matrix actual = buildBandMatrix(input);

    CPPUNIT_ASSERT_EQUAL(expected.size(), actual.size());
    CPPUNIT_ASSERT_EQUAL(expected[0].size(), actual[0].size());

    for (size_t i = 0; i < expected.size(); i++) {
        for (size_t j = 0; j < expected[0].size(); j++) {
            CPPUNIT_ASSERT_EQUAL(expected[i][j], actual[i][j]);
        }
    }
}
