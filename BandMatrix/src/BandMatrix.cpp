#include "BandMatrix.h"

Matrix create2DMatrix(const int size)
{
    std::vector<std::vector<int>> m(size);
    for (auto& line : m) {
        m.resize(size);
    }

    return m;
}

Matrix buildBandMatrix(const Matrix& m)
{
    return m;
}