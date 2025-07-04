#include "Matrix.h"
#include <cmath>
#include <iostream>

Matrix::Matrix(int order) : height(order), width(order) { 
    matrixArray = std::vector<std::vector<double>>(height, std::vector<double>(width));
}

Matrix::Matrix(int height, int width) : height(height), width(width) { 
    matrixArray = std::vector<std::vector<double>>(height, std::vector<double>(width));
}

// sx = sy = sz > 1: dilatação isotrópica
// sx = sy = sz < 1: contração isotrópica
// sx != sy ou sx != sz ou sz != sy: deformação ou escala anisotrópica
void Matrix::buildScale(double sx, double sy, double sz) {
    std::vector<double> a = {sx, sy, sz, 1};
    buildDiagonal(a);
}
// rx, ry e rz podem assumir 1 ou -1
// 1 sinal positivo = reflexão em torno do eixo
// 2 sinais positivos = reflexão em torno do plano
// 3 sinais negativos = reflexão em torno da origem (vetor simétrico)
void Matrix::buildReflexion(double rx, double ry, double rz) {
    std::vector<double> a = {rx, ry, rz, 1};
    buildDiagonal(a);
}

void Matrix::buildRotation(double angle, Vector axis) {

    // if (height == width && height == 4) {
    //     matrixArray[0][0] = pow(cos(angle), 2) - pow(sin(angle), 3);
    //     matrixArray[0][1] = -sin(angle) * cos(angle);
    //     matrixArray[0][2] = cos(angle) * sin(angle) - pow(sin(angle), 2) * cos(angle);
    //     matrixArray[0][3] = 0;
    //     matrixArray[1][0] = cos(angle) * pow(sin(angle), 2) + cos(angle) * sin(angle);
    //     matrixArray[1][1] = pow(cos(angle), 2);
    //     matrixArray[1][2] = pow(sin(angle), 2) - pow(cos(angle), 2) * sin(angle);
    //     matrixArray[1][3] = 0;
    //     matrixArray[2][0] = -cos(angle) * sin(angle);
    //     matrixArray[2][1] = sin(angle);
    //     matrixArray[2][2] = pow(cos(angle), 2);
    //     matrixArray[2][3] = 0;
    //     matrixArray[3][0] = 0;
    //     matrixArray[3][1] = 0;
    //     matrixArray[3][2] = 0;
    //     matrixArray[3][3] = 1;
    // }

}

void Matrix::buildRotationX(double angle) {
    if (height == width && height == 4) {
        buildDiagonal({1,1,1,1});
        matrixArray[0][0] = cos(angle);
        matrixArray[0][1] = -sin(angle);
        matrixArray[1][0] = sin(angle);
        matrixArray[1][1] = cos(angle);
    }
}
void Matrix::buildRotationY(double angle) {
    if (height == width && height == 4) {
        buildDiagonal({1,1,1,1});
        matrixArray[1][1] = cos(angle);
        matrixArray[1][2] = -sin(angle);
        matrixArray[2][1] = sin(angle);
        matrixArray[2][2] = cos(angle);
    }
}
void Matrix::buildRotationZ(double angle) {
    if (height == width && height == 4) {
        buildDiagonal({1,1,1,1});
        matrixArray[0][0] = cos(angle);
        matrixArray[0][2] = sin(angle);
        matrixArray[2][0] = -sin(angle);
        matrixArray[2][2] = cos(angle);
    }
}

void Matrix::buildTranslation(std::vector<double> valuesList) {
    if (valuesList.size() != height) {
        std::cout << "ERROR: TAMANHO DO VETOR TRANSLAÇÃO DIFERENTE DA ALTURA DA MATRIZ!" << std::endl;
        return;
    }

    for (int i = 0; i < height; ++i) {
        matrixArray[width-1][i] = valuesList[i];
    }
}

void Matrix::buildDiagonal (std::vector<double> valuesList) {
    if (height != width) {
        std::cout << "ERROR: MATRIZ NÃO QUADRADA NÃO POSSUI DIAGONAL!" << std::endl;
        return;
    }
    
    if (valuesList.size() != height) {
        std::cout << "ERROR: TAMANHO DO VETOR DIAGONAL DIFERENTE DA ORDEM DA MATRIZ!" << std::endl;
        return;
    }

    for (int i = 0, j = 0; i < height; ++i, ++j) {
        if (i == j) {
            matrixArray[i][j] = valuesList[i];
        } else {
            matrixArray[i][j] = 0;
        }
    }
}