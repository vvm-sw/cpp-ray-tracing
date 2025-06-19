#include "Vector.h"
#include <iostream>
#include <cmath>

/*
Classe de vetores.

A saber que:
    - x = componente x
    - y = componente y
    - z = componente z

A classe precisa ser instanciada passando as componentes x, y e z
*/

// Construtores
Vector::Vector() : x(0), y(0), z(0) {}
Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

// Print do vetor no formato <x, y, z>
void Vector::print() {
    std::cout << "<" << x << ", " << y << ", " << z << ">" << std::endl;
}

// Getters
const double& Vector::getX() const { return x; }
const double& Vector::getY() const { return y; }
const double& Vector::getZ() const { return z; }

// Setters
void Vector::setX(double newX) { x = newX; }
void Vector::setY(double newY) { y = newY; }
void Vector::setZ(double newZ) { z = newZ; }

// Calcula a magnitude (comprimento) do vetor
const double Vector::magnitude() const {
    return sqrt(x * x + y * y + z * z);
}

// Retorna uma versão normalizada (comprimento 1) do vetor
const Vector Vector::normalized() const {
    double mag = magnitude();
    if (mag == 0) return Vector(0, 0, 0); // Evita divisão por zero
    return Vector(this->getX()/mag, this->getY()/mag, this->getZ()/mag);
}
