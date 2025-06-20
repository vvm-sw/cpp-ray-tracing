#include "Matrix.h"


//double matrixArray[4][4] {0};
Matrix::Matrix()
{
}
void Matrix::buildScaleMatrix(double sx, double sy, double sz) {
    matrixArray[0][0] = sx;
    matrixArray[1][1] = sy;
    matrixArray[2][2] = sz;
    matrixArray[3][3] = 1;

    //return *this;
}