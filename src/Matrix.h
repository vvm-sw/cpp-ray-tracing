#include "Point.h"
#include "Vector.h"
#include <array>

class Matrix {
    private:
    //std::array<std:array<double, 4>, 4> matrixArray;
    // std::array<double, 4> matrixArray;
    

    public:
    Matrix();
    double matrixArray[4][4] {0};

    const Matrix& getScale (double sx, double sy, double sz); // TODO: Somente set e aí montamos a matriz pra cada operação???
    const Matrix& getReflexion(double sx, double sy, double sz); // Pode ser type ou get devolve matrixArray 'construído' para operação de mult matriz * vetor/ponto
    const Matrix& getRotation(double angle);
    const Matrix& getTranslation(Vector& v);
    const Matrix& getTranslation(Point& p);


    // void setMatrixArray(double x, double y, double z);
};