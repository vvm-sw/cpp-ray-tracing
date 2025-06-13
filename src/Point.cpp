#include "Point.h"
#include "Vector.h"

/*
Classe de pontos.

A saber que:
    - x = componente x
    - y = componente y
    - z = componente z

A classe precisa ser instanciada passando as componentes x, y e z
*/

// Construtores
Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

// Print do vetor no formato (x, y, z)
void Point::print(){
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

// Getters
double Point::getX() const { return x; }
double Point::getY() const { return y; }
double Point::getZ() const { return z; }

// Setters
void Point::setX(double newX) { x = newX; }
void Point::setY(double newY) { y = newY; }
void Point::setZ(double newZ) { z = newZ; }
