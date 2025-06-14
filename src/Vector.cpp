#include "Vector.h"
#include "Point.h"

/*
Classe de vetores.

A saber que:
    - x = componente x
    - y = componente y
    - z = componente z

A classe precisa ser instanciada passando as componentes x, y e z
*/

// Construtores
Vector::Vector() {}
Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

// Print do vetor no formato <x, y, z>
void Vector::print() {
    std::cout << "<" << x << ", " << y << ", " << z << ">" << std::endl;
}

// Getters
double Vector::getX() const { return x; }
double Vector::getY() const { return y; }
double Vector::getZ() const { return z; }

// Setters
void Vector::setX(double newX) { x = newX; }
void Vector::setY(double newY) { y = newY; }
void Vector::setZ(double newZ) { z = newZ; }

// Calcula a magnitude (comprimento) do vetor
double Vector::magnitude() const {
    return sqrt(x * x + y * y + z * z);
}

// Retorna uma versão normalizada (comprimento 1) do vetor
Vector Vector::normalized() const {
    double mag = magnitude();
    if (mag == 0) return Vector(0, 0, 0); // Evita divisão por zero
    return Vector(this->getX()/mag, this->getY()/mag, this->getZ()/mag);
}
