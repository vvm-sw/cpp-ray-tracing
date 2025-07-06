#include "Point.h"
#include <iostream>

/*
Classe de pontos.

A saber que:
    - x = componente x
    - y = componente y
    - z = componente z

A classe precisa ser instanciada passando as componentes x, y e z
*/

// Construtores
Point::Point() : x(0), y(0), z(0) {}
Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

// Print do vetor no formato (x, y, z)
void Point::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

// Getters
const double& Point::getX() const { return x; }
const double& Point::getY() const { return y; }
const double& Point::getZ() const { return z; }

// Setters
void Point::setX(double newX) { x = newX; }
void Point::setY(double newY) { y = newY; }
void Point::setZ(double newZ) { z = newZ; }
