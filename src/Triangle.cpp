#include "Triangle.h"
#include <iostream>

// Construtores
Triangle::Triangle(Point x, Point y, Point z) : x(x), y(y), z(z) {}

// Print do triangulo no formato <(x1, y1, z1), (x2, y2, z2), (x3, y3, 3z)>
void Triangle::print() {
    std::cout << "<" << 
    "(" << x.getX() << ", " << x.getY() << ", " << x.getZ() << ")" << 
    "(" << y.getX() << ", " << y.getY() << ", " << y.getZ() << ")" << 
    "(" << z.getX() << ", " << z.getY() << ", " << z.getZ() << ")" << 
    std::endl;
}

// Getters
Point Triangle::getX() const { return x; }
Point Triangle::getY() const { return y; }
Point Triangle::getZ() const { return z; }

// Setters
void Triangle::setX(Point newX) { x = newX; }
void Triangle::setY(Point newY) { y = newY; }
void Triangle::setZ(Point newZ) { z = newZ; }

// Interseção de um vetor com o triangulo
bool Triangle::hit(const Ray& r) const {

}