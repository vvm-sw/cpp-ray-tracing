#include "Point.h"
#include "Vector.h"
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

std::vector<double> Point::isMadeBy(Vector a, Vector b, Vector c, double t) {
    // Sendo P o ponto e a, b e c os vetores do triangulo da coordenada baricentrica; então
    // P.x = a.x + alfa * t (a poderia ser b ou c, basta escolher um unico ponto do triângulo)
    // P.y = a.y + beta * t
    // P.z = a.z + gama * t
    // Isto é:
    // (P.x - a.x) / t = alfa
    // (P.y - a.y) / t = beta
    // (P.z - a.z) / t = gama

    double alfa = (getX() - a.getX()) / (t);
    double beta = (getY() - a.getY()) / (t);
    double gama = (getZ() - a.getZ()) / (t);

    // Se alfa + beta + gama == 1 então o ponto está dentro do triângulo
    // Se alfa + beta + gama != 1 então o ponto está fora do triângulo
    if (alfa + beta + gama != 1) { return {0, 0, 0}; }

    return {alfa, beta, gama}
}