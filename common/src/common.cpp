#include "common.h"

Matrix create2DMatrix(size_t width, size_t height)
{
    Matrix m(height);
    for (auto& line : m) {
        line.resize(width);
    }

    return m;
}
