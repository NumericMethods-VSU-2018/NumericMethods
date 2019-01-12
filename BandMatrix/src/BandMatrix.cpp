#include "BandMatrix.h"

size_t getBandWidth(const Matrix& m)
{
    size_t width = 0;
    for (size_t row = 0; row < m.size(); row++) {
        size_t lastNonzeroColumn = 0;
        for (size_t column = row; column < m[row].size(); column++) {
            if (m[row][column] != 0) {
                lastNonzeroColumn = column;
            }
        }

        const size_t currentWidth = lastNonzeroColumn - row + 1;
        width = std::max(width, currentWidth);
    }

    return width;
}

Matrix buildBandMatrix(const Matrix& m)
{
    const size_t bandWidth = getBandWidth(m);
    const size_t height = m.size();
    Matrix res = create2DMatrix(bandWidth, height);
    for (size_t row = 0; row < height; row++) {
        for (size_t column = 0; column < bandWidth; column++) {
            const size_t originColumn = row + column;
            const auto value = originColumn < m[row].size() ?
                m[row][originColumn] : 0;

            res[row][column] = value;
        }
    }

    return res;
}