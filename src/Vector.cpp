#pragma once
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

class Vector{

private:
    double x;
    double y;
    double z;

public:
    //Construtores
    Vector() : x(0), y(0), z(0) {}
    Vector(double x, double y, double z) : x(x), y(y), z(z) {}

    //Print do vetor no formato <x, y, z>
    void print(){
        std::cout << "<" << x << ", " << y << ", " << z << ">" << std::endl;
    }

    //Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    // Setters
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
    void setZ(double newZ) { z = newZ; }
};