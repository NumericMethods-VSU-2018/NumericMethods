#include "BandMatrix.h"
#include <iostream>

int main()
{
    int size;
    std::cin >> size;

    Matrix m = create2DMatrix(size);
    Matrix band = buildBandMatrix(m);
    return 0;
}