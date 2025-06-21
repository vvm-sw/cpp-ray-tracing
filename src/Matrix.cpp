#include "Matrix.h"
#include <cmath>

Matrix::Matrix() { 
    matrixArray[3][3] = 1;
}
// sx = sy = sz > 1: dilatação isotrópica
// sx = sy = sz < 1: contração isotrópica
// sx != sy ou sx != sz ou sz != sy: deformação ou escala anisotrópica
void Matrix::buildScale(double sx, double sy, double sz) {
    buildDiagonal(sx, sy, sz);
}
// rx, ry e rz podem assumir 1 ou -1
// 1 sinal positivo = reflexão em torno do eixo
// 2 sinais positivos = reflexão em torno do plano
// 3 sinais negativos = reflexão em torno da origem (vetor simétrico)
void Matrix::buildReflexion(double rx, double ry, double rz) {
    buildDiagonal(rx, ry, rz);
}
void Matrix::buildRotation(double angle) {
    matrixArray[0][0] = pow(cos(angle), 2) - (pow(sin(angle), 3));
    matrixArray[0][1] = -sin(angle) * cos(angle);
    matrixArray[0][2] = (cos(angle) * sin(angle)) + (pow(sin(angle), 2)) * cos(angle);
    matrixArray[1][0] = sin(angle) + cos(angle) + (cos(angle) * pow(sin(angle), 2));
    matrixArray[0][1] = pow(cos(angle), 2);
    matrixArray[1][2] = pow(sin(angle), 2) + (pow(cos(angle), 2) * -sin(angle));  
    matrixArray[2][0] = cos(angle) * (-sin(angle));
    matrixArray[2][1] = sin(angle);
    matrixArray[2][2] = pow(cos(angle), 2);
}

void Matrix::buildTranslation(double x, double y, double z) {
    matrixArray[0][3] = x;
    matrixArray[1][3] = y; 
    matrixArray[2][3] = z;
}

void Matrix::buildDiagonal (double x, double y, double z) {
    matrixArray[0][0] = x;
    matrixArray[1][1] = y; 
    matrixArray[2][2] = z;
}