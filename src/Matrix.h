#pragma once

#include <cmath>
#include <vector>
#include "Vector.h"

class Matrix {
    public:
    std::vector<std::vector<double>> matrixArray;
    int height;
    int width;

    Matrix(int height, int width);
    Matrix(int order);

    void buildScale(double sx, double sy, double sz);
    void buildReflexion(double sx, double sy, double sz);
    void buildRotation(double angle, Vector axis);
    void Matrix::buildRotationX(double angle);
    void Matrix::buildRotationY(double angle);
    void Matrix::buildRotationZ(double angle);
    void buildTranslation(std::vector<double> valuesList);
    void buildDiagonal(std::vector<double> valuesList);
};